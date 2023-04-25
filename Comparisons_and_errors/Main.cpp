#include<iostream>
#include<fstream>
#include<string>

void Insert_In_File(double* new_array, size_t count, std::string name)
{
	std::fstream stream;
	stream.open(name, std::fstream::in | std::fstream::out);

	if (stream.is_open())
	{
		for (size_t i = 0; i < count; i++)
			stream << new_array[i] << " ";
		stream << "\n";
	}
	else
		throw "The file isn't exist";
	stream.close();
}
void Insert_In_File_With_Const(double* new_array, size_t count, std::string name,double _const)
{
	std::fstream stream;
	stream.open(name, std::fstream::in | std::fstream::out);

	if (stream.is_open())
	{
		for (size_t i = 0; i < count; i++)
			stream << new_array[i] << " ";
		stream << "\n";
		stream << _const;
	}
	else
		throw "The file isn't exist";
	stream.close();
}

[[noreturn]] void InputArray(std::string name_of_file, double* _array)
{
	std::ifstream f_in;
	double temp_buff = 0.0;
	size_t i = 0.0;


	f_in.open(name_of_file);
	if (f_in.is_open())
	{
		i = 0;
		while (!f_in.eof())
		{
			f_in >> temp_buff;
			_array[i] = temp_buff;
			i++;
		}
	}
	else
		throw "file wasn't opened";
	f_in.close();
}

size_t GetCount(std::string name_of_file)
{
	std::ifstream f_in;
	size_t size_of_ff = 0.0;
	double temp_buff = 0.0;

	f_in.open(name_of_file);
	if (f_in.is_open())
	{
		while (!f_in.eof())
		{
			f_in >> temp_buff;
			size_of_ff++;
		}
	}
	else
		throw "file wasn't opened";
	f_in.close();
	size_of_ff--;
	return size_of_ff;
}


int main()
{
	std::string name_good_solut = "GoodSolution.txt";
	std::string name_of_current_file = "CompareWithGoodSol.txt";

	double temp_buff = 0.0;
	size_t size_of_GS = 0;
	size_t size_of_CF = 0;
	size_t Almost_Jacobian = 0;
	double max = 0.0;
	double tmp = 0.0;

	size_of_GS = GetCount(name_good_solut);
	size_of_CF = GetCount(name_of_current_file);

	double* array_from_GS = new double[size_of_GS];
	double* array_from_CF = new double[size_of_CF];
	double* array_of_ABS = new double[size_of_CF];
	double* array_of_REL = new double[size_of_CF];

	InputArray(name_good_solut, array_from_GS);
	InputArray(name_of_current_file, array_from_CF);

	Almost_Jacobian = ((size_of_GS - 1) / (size_of_CF - 1));
	/*for (size_t i = 0; i < size_of_GS; i++)
	{
		std::cout << array_from_GS[i] << ' ';
	}*/

	for (size_t q = 0; q < size_of_CF; q++)
	{
		array_of_ABS[q] = abs(array_from_GS[q * Almost_Jacobian] - array_from_CF[q]);
		std::cout << q << ' ' << array_from_GS[q * Almost_Jacobian] << " - " << array_from_CF[q] << " = " << array_of_ABS[q] << std::endl;
	}

	for (size_t i = 0; i < size_of_CF; i++)
	{
		if (array_of_ABS[i] > max) max = array_of_ABS[i];
	}

	Insert_In_File_With_Const(array_of_ABS, size_of_CF, "outputABS.txt", max);
	max = 0.0;

	for (size_t q = 0; q < size_of_CF; q++)
	{
		if (array_from_GS[q * Almost_Jacobian] > array_from_CF[q]) tmp = array_from_GS[q * Almost_Jacobian];
		else
			tmp = array_from_CF[q];
		array_of_REL[q] = (abs(array_from_GS[q * Almost_Jacobian] - array_from_CF[q])/tmp);
		//std::cout << q << ' ' << array_from_GS[q * Almost_Jacobian] << " - " << array_from_CF[q] << " = " << array_of_ABS[q] << std::endl;
	}

	for (size_t i = 0; i < size_of_CF; i++)
	{
		if (array_of_REL[i] > max) max = array_of_REL[i];
	}
	Insert_In_File_With_Const(array_of_REL, size_of_CF, "outputREL.txt", max);
	return 0;
}