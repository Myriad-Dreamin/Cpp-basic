#pragma once
#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

namespace MatrixSpace
{
	/*
	 * MatrixCalculateError:
	 *
	 * ��Matrix��Ԫ���㲻ƥ��ʱ��������Exception
	 * ʹ��MatrixCalculateError("Exception Descript...")����һ��Exception
	 */
	class MatrixCalculateError
	{
	public:

		MatrixCalculateError();

		MatrixCalculateError(const char *str);

		MatrixCalculateError(std::string &str);

		MatrixCalculateError(const MatrixCalculateError &rhs);

		const char *what() const;

	protected:

		std::string msg;
	};

	/*
	 * MatrixReferenceError:
	 *
	 * �����ʳ�����Matrix���д�Сʱ�������˴���
	 * ʹ��MatrixCalculateError("Exception Descript...")����һ��Exception
	 */
	class MatrixReferenceError
	{
	public:

		MatrixReferenceError();

		MatrixReferenceError(const char *str);

		MatrixReferenceError(std::string &str);

		MatrixReferenceError(const MatrixReferenceError &rhs);

		const char *what() const;

	protected:

		std::string msg;
	};

	/*
	 * Matrix<MatrixType>:
	 *
	 * һ�����͵ľ����֧࣬�ּӼ�����
	 * ����㶨����Ԥ����� SAFEMATRIX ����������ܵĴ��󣬷�����������������о�ֹ���Ǵ����ġ�
	 *
	 * Unsafe Matrix:
	 * ע������ĳ�ʼ��������new��ȷ�����new��delete���ʹ��
	 * ע������ļӼ����������new���벻Ҫʹ�������㣬��ᵼ���ڴ�й©
	 *
	 * Safe Matrix:
	 * ��ֹ�������Խ��
	 */
	template <typename MatrixType>
	class Matrix
	{
	private:

		int row, col, rmc;

		MatrixType *aloc_array;

		template <typename MtxType>
		friend std::ostream &operator<< (std::ostream &os, Matrix<MtxType> const &out_mat);

	public:
		/*
		 * Ĭ�Ϲ��캯��
		 *
		 * ��ʱ�����������ֵ��Ϊ0,����ָ��Ϊnullptr
		 */
		Matrix();

		/*
		 * ������������Ĺ��캯��
		 * @size_row: �еĴ�С
		 * @size_col: �еĴ�С
		 *
		 * ��ʱ�����������ֵΪ(size_row, size_col)
		 * ����ǡ��֧��[0 ~ (size_row - 1)][0 ~ (size_col - 1)]�ķ���
		 * ...
		 */
		Matrix(int const size_row, int const size_col);

		/*
		 * �������������
		 *
		 * �����������������ڴ�
		 */
		~Matrix();

		/*
		 * []��������
		 *
		 * ������ľ���ʵ����Mat��ʹ��Mat[x][y]���ʵ�x�е�y�е�Ԫ��
		 * x��0 ~ (size_row - 1)֮�䣬y��0 ~ (size_col - 1)֮��
		 */
		inline MatrixType *operator[] (int const sel_row) const;

		/*
		 * +��������
		 * @arg1: Matrix<MatrixType>
		 * @arg2: Matrix<MatrixType>
		 * @res: Matrix<MatrixType>*
		 *
		 * ������ľ���ʵ����A, B��ʹ��һ��ָ�����������C = A + B
		 * ʹ��delete C����������������������
		 * Ҫ��A��B�����д�С��ͬ
		 */
		Matrix<MatrixType> *operator+ (Matrix<MatrixType> const &right_mat) const;

		/*
		 * -��������
		 * @arg1: Matrix<MatrixType>
		 * @arg2: Matrix<MatrixType>
		 * @res: Matrix<MatrixType>*
		 *
		 * ������ľ���ʵ����A, B��ʹ��һ��ָ�����������C = A - B
		 * ʹ��delete C����������������������
		 * Ҫ��A��B�����д�С��ͬ
		 */
		Matrix<MatrixType> *operator- (Matrix<MatrixType> const &right_mat) const;

		/*
		 * =��������
		 * @arg1: Matrix<MatrixType>
		 *
		 * ��ɸ�ֵ���߼����
		 */
		const Matrix<MatrixType> operator= (Matrix<MatrixType> const &right_mat);

		/*
		 * initfs
		 *
		 * ���ݾ����ʼ����row��col������˳�����MatrixType���͵�Ԫ��.
		 */
		void initfs();
	};
}

#endif
