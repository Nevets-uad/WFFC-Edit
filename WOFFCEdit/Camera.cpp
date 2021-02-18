#include "Camera.h"

Camera::Camera()
{
	//functional
	m_movespeed = 0.30;
	m_camRotRate = 3.0;

	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camUp.x = 0.0f;
	m_camUp.y = 1.0f;
	m_camUp.z = 0.0f;
	
	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;

	m_focusedObject = nullptr;

	m_yaw = -90.0f;
	m_pitch = 0.0f;
	m_roll = 0.0f;
	m_firstMouse = true;
	m_lastX = 0.0f;
	m_lastY = 0.0f;
	m_sensitivity = 0.3f;
	m_freeCam = false;
	m_camChanged = false;
}

Camera::~Camera()
{
}

void Camera::Update(DX::StepTimer const &timer)
{
	//TODO  any more complex than this, and the camera should be abstracted out to somewhere else
	if(m_freeCam)
		Turn();
	
	if (m_focusedObject)
	{
		DirectX::SimpleMath::Vector3 objectDirection = m_focusedObject->m_position - m_camPosition;
		objectDirection.Normalize();
		m_camLookDirection = objectDirection;
	}
	//camera motion is on a plane, so kill the y component of the look direction
	DirectX::SimpleMath::Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;

	float cosR, cosP, cosY; //temp values for sin/cos from
	float sinR, sinP, sinY;
	// Roll, Pitch and Yall are variables stored by the camera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY = cosf(planarMotionVector.z * 3.1415 / 180.0f);
	cosP = cosf(planarMotionVector.y * 3.1415 / 180.0f);
	cosR = cosf(planarMotionVector.x * 3.1415 / 180.0f);
	sinY = sinf(planarMotionVector.z * 3.1415 / 180.0f);
	sinP = sinf(planarMotionVector.y * 3.1415 / 180.0f);
	sinR = sinf(planarMotionVector.x * 3.1415 / 180.0f);

	if (!m_freeCam && !m_focusedObject)
	{
		//create look direction from Euler angles in m_camOrientation
		m_camLookDirection.x = sin((m_camOrientation.y)*3.1415 / 180);
		m_camLookDirection.z = cos((m_camOrientation.y)*3.1415 / 180);
		m_camLookDirection.Normalize();
	}
	// Up Vector
	m_camUp.x = (-cosY * sinR - sinY * sinP * cosR);
	m_camUp.y = (cosP * cosR);
	m_camUp.z = (-sinY * sinR - sinP * cosR * -cosY);

	//create right vector from look Direction
	m_camLookDirection.Cross(m_camUp, m_camRight);

	//update lookat point
	if (m_focusedObject)
		m_camLookAt = m_focusedObject->m_position;
	else
		m_camLookAt = m_camPosition + m_camLookDirection;

	
	//apply camera vectors
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_camPosition, m_camLookAt, m_camUp);

	//Reset the camera being changed each frame
	if(m_camChanged)
		m_camChanged = false;
}

void Camera::RotateCameraLeft()
{
	m_camOrientation.y += m_camRotRate;
}

void Camera::RotateCameraRight()
{
	m_camOrientation.y -= m_camRotRate;
}

void Camera::MoveForward()
{
	m_camPosition += m_camLookDirection * m_movespeed;
}

void Camera::MoveBackward()
{
	m_camPosition -= m_camLookDirection * m_movespeed;
}

void Camera::MoveRight()
{
	m_camPosition += m_camRight * m_movespeed;
}

void Camera::MoveLeft()
{
	m_camPosition -= m_camRight * m_movespeed;
}

void Camera::Turn()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	if (m_firstMouse)
	{
		m_lastX = mousePos.x;
		m_lastY = mousePos.y;
		m_firstMouse = false;
	}

	float xoffset = mousePos.x - m_lastX;
	float yoffset = m_lastY - mousePos.y; // reversed since y-coordinates go from bottom to top
	m_lastX = mousePos.x;
	m_lastY = mousePos.y;


	xoffset *= m_sensitivity;
	yoffset *= m_sensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	DirectX::SimpleMath::Vector3 forward;
	
	forward.x = (cos(DirectX::XMConvertToRadians(m_yaw)) * cos(DirectX::XMConvertToRadians(m_pitch)));
	forward.y = (sin(DirectX::XMConvertToRadians(m_pitch)));
	forward.z = (sin(DirectX::XMConvertToRadians(m_yaw)) * cos(DirectX::XMConvertToRadians(m_pitch)));
	forward.Normalize();
	m_camLookDirection = forward;
}

void Camera::SetFreeCam()
{
	m_freeCam = !m_freeCam;
}

void Camera::HandleInput(InputCommands &Input)
{
	//Right rotation
	if (Input.rotRight)
		RotateCameraRight();
	//Left rotation
	if (Input.rotLeft)
		RotateCameraLeft();
	//Forward movement
	if (Input.forward)
		MoveForward();
	//Backward movement
	if (Input.back)
		MoveBackward();
	//Right movement
	if (Input.right)
		MoveRight();
	//Left movement
	if (Input.left)
		MoveLeft();
	//Space
	if (Input.space && !m_camChanged)
	{
		SetFreeCam();
		m_camChanged = true;
	}
}




