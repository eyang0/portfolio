#include <iostream>
#include <stdexcept>
#include <cstring>
#include "str.h"

using namespace std;

// Add your implementations here.

Str::Str()
{
	data_ = NULL;
	size_ = 0;
}

Str::Str(const char* s)
{
	if(s == NULL)
	{
		data_ = NULL;
		size_ = 0;
	}
	else
	{
		size_ = strlen(s);
		//dynamically allocating the char array
		data_ = new char[size_];
		for(int i = 0; i<size_; i++)
		{
			data_[i] = s[i];
		}
	}
}

Str::~Str()
{
	delete [] data_;
}

//copy constructor
Str::Str(const Str& other)
{
	this->size_ = other.size_;
	this->data_ = new char[size_];
	for(int i = 0; i<size_; i++)
	{
		this->data_[i] = other.data_[i];
	}
}


Str& Str::operator=(const Str& other)
{
	if(this == &other)
	{
		return *this;
	}

	if(this->data_ != NULL)
	{
		delete [] this->data_;
	}

	//creating deep copy
	this->size_ = other.size_;
	this->data_ = new char[size_];
	for(int i = 0; i<size_; i++)
	{
		this->data_[i] = other.data_[i];
	}

	return *this;

}


Str& Str::operator=(const char* s)
{
	if(s == NULL)
	{
		this->data_ = NULL;
		this->size_ = 0;
		return *this;
	}
	if(this->data_ == s)
	{
		return *this;
	}

	if(this->data_ != NULL)
	{
		delete [] this->data_;
	}

	//creating deep copy
	this->size_ = strlen(s);
	this->data_ = new char[size_];
	for(int i = 0; i<size_; i++)
	{
		this->data_[i] = s[i];
	}

	return *this;
}


Str& Str::operator+=(const Str& s)
{
	if(s.data_ == NULL)
	{
		return *this;
	}

	char* temp = this->data_;	
	int temp_size = this->size_;	
	
	//get the size of the new combined char*
	this->size_ = (this->size_) + s.size_;
	this->data_ = new char[size_];

	//copying in old Str data_
	for(int i = 0; i<temp_size; i++)
	{
		this->data_[i] = temp[i];
	}
	//adding the new Str data_
	for(int j = temp_size; j<this->size_; j++)
	{
		this->data_[j] = s.data_[j-temp_size];
	}

	if(temp!= NULL)
	{
		delete [] temp;
	}

	return *this;
}


Str& Str::operator+=(const char* s)
{
	if(s == NULL)
	{
		return *this;
	}

	char* temp = this->data_;	
	int temp_size = this->size_;
		
	//get the size of the new combined char*
	this->size_ = (this->size_) + strlen(s);
	this->data_ = new char[size_];

	//adding old Str data_
	for(int i = 0; i<temp_size; i++)
	{
		this->data_[i] = temp[i];
	}

	//adding new char* 
	for(int j = temp_size; j<this->size_; j++)
	{
		this->data_[j] = s[j-temp_size];
	}

	if(temp!= NULL)
	{
		delete [] temp;
	}

	return *this;
}


size_t Str::size() const
{
	return size_;
}



char& Str::operator[](unsigned int i)
{
	if(i < (unsigned int)0 || i>= (unsigned int)(this->size_))
	{
		throw std::out_of_range("Index is out of range");
	}
	return this->data_[i];
}


char const & Str::operator[](unsigned int i) const
{
	if(i < (unsigned int)0 || i>= (unsigned int)(this->size_))
	{
		throw std::out_of_range("Index is out of range");
	}
	return this->data_[i];
}


Str Str::operator+(const char* rhs  ) const
{

	Str temp;
	temp.size_ = this->size_ + strlen(rhs);
	temp.data_ = new char[temp.size_];

	for(int i = 0; i<this->size_; i++)
	{
		temp.data_[i] = this->data_[i];
	}
	for(int j = this->size_; j<temp.size_; j++)
	{
		temp.data_[j] = rhs[j-this->size_];
	}

	return temp;
}

Str Str::operator+(const Str& s) const 
{

	Str temp;
	temp.size_ = this->size_ + s.size_;
	temp.data_ = new char[temp.size_];
	
	for(int i = 0; i<this->size_; i++)
	{
		temp.data_[i] = this->data_[i];
	}
	for(int j = this->size_; j<temp.size_; j++)
	{
		temp.data_[j] = s.data_[j-this->size_];
	}

	return temp;
}


bool Str::operator==(const Str& s)
{
	if(this->size_ != s.size_)
	{
		return false;
	}
	else
	{
		return strncmp(this->data_, s.data_, this->size_) == 0;
	}
}

bool Str::operator!=(const Str& s)
{
	if(this->size_ != s.size_)
	{
		return true;
	}
	else
	{
		return strncmp(this->data_, s.data_, this->size_) != 0;
	}
}

bool Str::operator<(const Str& s)
{
	int smallest_size = s.size_;
	if(this->size_ <= s.size_)
	{
		smallest_size = this->size_;
	}

	if(strncmp(this->data_, s.data_, smallest_size) < 0)
	{
		return true;
	}

	if(strncmp(this->data_, s.data_, smallest_size) == 0)
	{
		return this->size_ < s.size_;
	}

	return false;
}


bool Str::operator>(const Str& s)
{

	int smallest_size = s.size_;
	if(this->size_ <= s.size_)
	{
		smallest_size = this->size_;
	}

	if(strncmp(this->data_, s.data_, smallest_size) > 0)
	{
		return true;
	}

	if(strncmp(this->data_, s.data_, smallest_size) == 0)
	{
		return this->size_ > s.size_;
	}

	return false;
}



std::ostream& operator<<(std::ostream& ostr, const Str& s)
{
	if(s.data_ == NULL)
	{
		ostr << "";
	}
	else
	{
		for(int i = 0; i<s.size_; i++)
		{
			ostr << s.data_[i];
		}
	}
	return ostr;
}




std::istream& operator>>(std::istream& istr, Str& s)
{
  std::string stemp;
  istr >> stemp;
  s = stemp.c_str();
  return istr;
}

