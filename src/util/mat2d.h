/** 
 * @file 
 * @brief 2D Transformation Matrix
 * @author Miroslav Nemecek <Panda38@seznam.cz>
 * @see CanvasGroup
*/

#ifndef _MAT2D_H
#define _MAT2D_H

#include "pico/double.h"
#include "define.h"

/// Transformation matrix
template <typename m2type> class cMat2D 
{
public:

	// transformation matrix
	m2type m11, m12, m13;
	m2type m21, m22, m23;

	/// Transform X
	inline m2type GetX(m2type x, m2type y) const
	{
		return x*m11 + y*m12 + m13;
	}	

	/// Transform Y
	inline m2type GetY(m2type x, m2type y) const
	{
		return x*m21 + y*m22 + m23;
	}	

	/// Set unit matrix
	inline void Unit()
	{
		m11 = 1; m12 = 0; m13 = 0;
		m21 = 0; m22 = 1; m23 = 0;
	}

	/// Copy matrix
	inline void Copy(const cMat2D* m)
	{
		m11 = m->m11; m12 = m->m12; m13 = m->m13;
		m21 = m->m21; m22 = m->m22; m23 = m->m23;
	}

	/**
	 * @brief Translate in X direction
	 * @details
	 * <pre>
	 *  1  0 tx   m11 m12 m13   m11 m12 m13+tx
	 *  0  1  0 * m21 m22 m23 = m21 m22 m23
	 *  0  0  1     0   0   1    0   0   1
	 * </pre>
	*/
	inline void TransX(m2type tx)
	{
		m13 += tx;
	}
	
	/**
	 * @brief Translate in Y direction
	 * @details
	 * <pre>
	 *  1  0  0   m11 m12 m13   m11 m12 m13
	 *  0  1 ty * m21 m22 m23 = m21 m22 m23+ty
	 *  0  0  1     0   0   1    0   0   1
	 * </pre>
	*/
	inline void TransY(m2type ty)
	{
		m23 += ty;
	}

	/**
	 * @brief Scale in X direction
	 * @details
	 * <pre>
	 *  sx 0  0   m11 m12 m13    m11*sx m12*sx m13*sx
	 *  0  1  0 * m21 m22 m23  = m21    m22    m23
	 *  0  0  1     0   0   1      0      0      1
	 * </pre>
	*/
	inline void ScaleX(m2type sx)
	{
		m11 *= sx;
		m12 *= sx;
		m13 *= sx;
	}	

	/**
	 * @brief Scale in Y direction
	 * @details
	 * <pre>
	 *  1  0  0   m11 m12 m13    m11    m12    m13
	 *  0  sy 0 * m21 m22 m23  = m21*sy m22*sy m23*sy
	 *  0  0  1     0   0   1      0      0      1
	 * </pre>
	*/
	inline void ScaleY(m2type sy)
	{
		m21 *= sy;
		m22 *= sy;
		m23 *= sy;
	}	
	
	/**
	 * @brief Rotate, using sin and cos
	 * @details
	 * <pre>
	 *  cosa -sina  0   m11 m12 m13   m11*cosa-m21*sina  m12*cosa-m22*sina  m13*cosa-m23*sina
	 *  sina  cosa  0 * m21 m22 m23 = m11*sina+m21*cosa  m12*sina+m22*cosa  m13*sina+m23*cosa
	 *   0      0   1     0   0   1           0                    0                 1
	 * </pre>
	*/
	inline void RotSC(m2type sina, m2type cosa)
	{
		m2type t1 = m11;
		m2type t2 = m21;
		m11 = t1*cosa - t2*sina;
		m21 = t1*sina + t2*cosa;

		t1 = m12;
		t2 = m22;
		m12 = t1*cosa - t2*sina;
		m22 = t1*sina + t2*cosa;

		t1 = m13;
		t2 = m23;
		m13 = t1*cosa - t2*sina;
		m23 = t1*sina + t2*cosa;
	}

	/// Rotate, using angle
	inline void Rot(m2type a)
	{
		this->RotSC(sin(a), cos(a));
	}

	/// Rotate by 90 deg (sina=1, cosa=0)
	inline void Rot90()
	{
		m2type t = m11;
		m11 = -m21;
		m21 = t;

		t = m12;
		m12 = -m22;
		m22 = t;

		t = m13;
		m13 = -m23;
		m23 = t;
	}

	/// Rotate by 180 deg (=flipX and flipY) (sina=0, cosa=-1)
	inline void Rot180()
	{
		m11 = -m11;
		m21 = -m21;
		m12 = -m12;
		m22 = -m22;
		m13 = -m13;
		m23 = -m23;
	}

	/// Rotate by 270 deg (sina=-1, cosa=0)
	inline void Rot270()
	{
		m2type t = m11;
		m11 = m21;
		m21 = -t;

		t = m12;
		m12 = m22;
		m22 = -t;

		t = m13;
		m13 = m23;
		m23 = -t;
	}

	/**
	 * @brief Shear in X direction
	 * @details
	 * <pre>
	 *  1  dx 0   m11 m12 m13   m11+m21*dx m12+m22*dx m13+m23*dx
	 *  0  1  0 * m21 m22 m23 = m21        m22        m23
	 *  0  0  1     0   0   1     0          0          1
	 * </pre>
	*/
	inline void ShearX(m2type dx)
	{
		m11 += m21*dx;
		m12 += m22*dx;
		m13 += m23*dx;
	}

	/**
	 * @brief Shear in Y direction
	 * @details
	 * <pre>
	 *  1  0  0   m11 m12 m13   m11        m12        m13
	 *  dy 1  0 * m21 m22 m23 = m21+m11*dy m22+m12*dy m23+m13*dy
	 *  0  0  1     0   0   1     0          0          1
	 * </pre>
	*/
	inline void ShearY(m2type dy)
	{
		m21 += m11*dy;
		m22 += m12*dy;
		m23 += m13*dy;
	}

	/**
	 * @brief Flip in Y direction
	 * @details
	 * <pre>
	 *  1  0  0   m11 m12 m13     m11   m12    m13
	 *  0 -1  0 * m21 m22 m23  = -m21  -m22   -m23
	 *  0  0  1     0   0   1      0     0      1
	 * </pre>
	*/
	inline void FlipY()
	{
		m21 = -m21;
		m22 = -m22;
		m23 = -m23;
	}	

	/**
	 * @brief Flip in X direction
	 * @details
	 * <pre>
	 *  -1 0  0   m11 m12 m13    -m11  -m12   -m13
	 *  0  1  0 * m21 m22 m23  = m21    m22    m23
	 *  0  0  1     0   0   1      0      0      1
	 * </pre>
	*/
	inline void FlipX()
	{
		m11 = -m11;
		m12 = -m12;
		m13 = -m13;
	}
};

#define TOFRACT(f) ((int)((f)*FRACTMUL + (((f) < 0) ? -0.5f : 0.5f)))

/// @addtogroup CanvasGroup
/// @{

/**
 * @brief 2D Transformation Matrix
 * @details Some rendering functions use the cMat2Df transformation matrix to define image transformation. The matrix has 
 * 6 numeric elements of float type. The transformation is prepared by setting the initial state with the Unit function and 
 * then entering the transformations one by one. Using the matrix, operations are performed on the image as if the
 *  operations were entered sequentially.
*/
class cMat2Df : public cMat2D<float>
{
public:
	/**
	 * @brief Prepare transformation matrix (for DrawImgMat() function)
	 * @details The order of operations is chosen as if the image is first moved to the point tx and ty, scaled, skewed, then 
	 * rotated and finally moved to the target coordinates.
	 * @param ws Source image width 
	 * @param hs Source image height
	 * @param x0 Reference point X on source image
	 * @param y0 Reference point Y on source image
	 * @param wd Destination image width (negative = flip image in X direction)
	 * @param hd Destination image height (negative = flip image in Y direction)
	 * @param shearx Shear image in X direction
	 * @param sheary Shear image in Y direction
	 * @param r Rotate image (angle in radians)
	 * @param tx Shift in X direction (ws = whole image width)
	 * @param ty Shift in Y direction (hs = whole image height)
	*/
	void PrepDrawImg(int ws, int hs, int x0, int y0, int wd, int hd,
		float shearx, float sheary, float r, float tx, float ty);

	/**
	 * @brief Export matrix to int array[6]
	 * @details After transformation, the lower 12 bits of the number contain the decimal part of the number, the upper 20 bits 
	 * contain the integer part of the number. Rendering functions require this integer form of the transformation matrix.
	*/
	void ExportInt(int* mat) const;
};

/// @}

#endif // _MAT2D_H
