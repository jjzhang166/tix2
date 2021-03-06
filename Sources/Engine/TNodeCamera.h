/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	class TNodeCamera : public TNode
	{
	public:
		enum E_CAMERA_FLAG
		{
			ECAMF_MAT_VIEW_DIRTY		= 1 << 0,
			ECAMF_MAT_PROJECTION_DIRTY	= 1 << 1,
			ECAMF_MAT_VP_DIRTY			= 1 << 2,

			ECAMF_MAT_VIEW_UPDATED		= 1 << 8,
			ECAMF_MAT_PROJ_UPDATED		= 1 << 9,
			ECAMF_MAT_VP_UPDATED		= 1 << 10,
			ECAMF_MAT_UPDATED			= (ECAMF_MAT_VIEW_UPDATED | ECAMF_MAT_VP_UPDATED | ECAMF_MAT_PROJ_UPDATED),

			ECAMF_LOCK_ACTION			= 1 << 12,
		};
	public:
		TNodeCamera(TNode* parent, 
						const vector3df& pos = vector3df(-500, 0, 0), const vector3df& target = vector3df(0, 0, 0));
		virtual ~TNodeCamera();

		virtual void RegisterElement();

		virtual void CreateRenderThreadNode() override {};

		virtual void SetPosition(const vector3df& pos);

		//! Sets the projection matrix of the camera.
		/** The matrix4 class has some methods
			to build a projection matrix. e.g: matrix4::buildProjectionMatrixPerspectiveFov.
			Note that the matrix will only stay as set by this method until one of
			the following Methods are called: setNearValue, setFarValue, setAspectRatio, setFOV.
			\param projection The newly projection matrix of the camera.
			\param isOrthogonal Set this to true if the matrix is an orthogonal one (e.g.
			from matrix4::buildProjectionMatrixOrtho(). */
		virtual void SetProjectionMatrix(const matrix4& projection, bool isOrthogonal = false);

		//! Gets the current projection matrix of the camera
		//! \return Returns the current projection matrix of the camera.
		virtual const matrix4& GetProjectionMatrix() const;

		//! Gets the current view matrix of the camera
		//! \return Returns the current view matrix of the camera.
		virtual const matrix4& GetViewMatrix() const;

		//! sets the look at target of the camera
		//! \param pos: Look at target of the camera.
		virtual void SetTarget(const vector3df& pos);

		//! Gets the current look at target of the camera
		//! \return Returns the current look at target of the camera
		virtual const vector3df& GetTarget() const;

		//! Sets the up vector of the camera.
		//! \param pos: New upvector of the camera.
		virtual void SetUpVector(const vector3df& pos);

		//! Gets the up vector of the camera.
		//! \return Returns the up vector of the camera.
		virtual const vector3df& GetUpVector() const;

		//! Gets distance from the camera to the near plane.
		//! \return Value of the near plane of the camera.
		virtual f32 GetNearValue() const;

		//! Gets the distance from the camera to the far plane.
		//! \return Value of the far plane of the camera.
		virtual f32 GetFarValue() const;

		//! Get the aspect ratio of the camera.
		//! \return The aspect ratio of the camera.
		virtual f32 GetAspectRatio() const;

		//! Gets the field of view of the camera.
		//! \return Field of view of the camera
		virtual f32 GetFOV() const;

		void LockAction(bool lock)
		{
			if (lock)
				CameraFlags	|= ECAMF_LOCK_ACTION;
			else
				CameraFlags	&= ~ECAMF_LOCK_ACTION;
		}

		virtual const vector3df& GetCamDir()
		{
			return	CamDir;
		}
		virtual const vector3df& GetHorVector()
		{
			return	HorVector;
		}
		virtual const vector3df& GetVerVector()
		{
			return	VerVector;
		}

		//! Sets the value of the near clipping plane. (default: 1.0f)
		virtual void SetNearValue(f32 zn);

		//! Sets the value of the far clipping plane (default: 2000.0f)
		virtual void SetFarValue(f32 zf);

		//! Sets the aspect ratio (default: 4.0f / 3.0f)
		virtual void SetAspectRatio(f32 aspect);

		//! Sets the field of view (Default: PI / 3.5f)
		virtual void SetFOV(f32 fovy);

		//! Returns the view area. Sometimes needed by bsp or lod render nodes.
		virtual const SViewFrustum* GetViewFrustum() const;

		//! Get a ray from the screen coord.
		virtual void GetRayFrom2DPoint(const vector2di& pos, line3df &ray, float length = 1000.f);
		virtual void GetRayFrom2DPoint(const vector2df& pos, line3df &ray, float length = 1000.f);
		virtual void GetRayFrom2DPointWithViewport(const rectf& vp, const vector2df& pos, line3df &ray, float length = 1000.f);

		//! Convert 3d position into 2d screen space
		TI_API	vector2df	Convert3Dto2D(const vector3df& pos);

		const SViewFrustum&	GetFrustum()
		{
			return	ViewArea;
		}

		uint32	GetCameraFlags()
		{
			return CameraFlags;
		}
	protected:

		virtual void RecalculateProjectionMatrix();
		virtual void RecalculateViewMatrix();
		virtual void RecalculateViewArea();

	protected:
		uint32 CameraFlags;

		vector3df Target;
		vector3df UpVector;

		vector3df CamDir;
		vector3df HorVector;
		vector3df VerVector;

		f32 Fovy;	// Field of view, in radians. 


		f32 Aspect;	// Aspect ratio. 
		f32 ZNear;	// value of the near view-plane. 
		f32 ZFar;	// Z-value of the far view-plane.

		SViewFrustum ViewArea;
	};

} // end namespace tix

