#pragma once

template <typename T>
struct Array
{
	T *data;
	int capacity;
	int length;

	inline Array()
	{
		this->data = 0;
		this->capacity = 0;
		this->length = 0;
	}

	inline void Reserve(int initial_capacity)
	{
		assert(initial_capacity > 0);

		this->data = 0;
		this->capacity = initial_capacity;
		this->length = 0;

		this->data = (T *)malloc(initial_capacity * sizeof(T));
	}

	inline T &operator[](int index)
	{
		assert(index >= 0 && index < this->length);
		return this->data[index];
	}

	inline const T operator[](int index) const
	{
		assert(index >= 0 && index < this->length);
		return this->data[index];
	}

	void Push(T elem)
	{
		if (this->capacity == 0)
		{
			Resize(1);
		}
		else if (this->length == this->capacity)
		{
			Resize(2 * this->capacity);
		}

		this->data[length] = elem;
		this->length++;
	}

	void Resize(int new_capacity)
	{
		assert(new_capacity > 0);

		this->data = (T *)realloc(this->data, new_capacity * sizeof(T));

		if (new_capacity < this->capacity)
		{
			if (this->length > new_capacity)
			{
				this->length = new_capacity;
			}
		}

		this->capacity = new_capacity;
	}

	void Pop()
	{
		if (this->length > 0)
		{
			this->length--;
		}
	}

	void Clear()
	{
		this->length = 0;
	}

	int SizeInBytes()
	{
		return this->length * sizeof(T);
	}

	void Destroy()
	{
		free(this->data);
	}
};