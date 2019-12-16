template <typename T>
class Vector
{
public:
	Vector();
	Vector(const Vector& src);
	Vector(size_t size);
	Vector(size_t size, T fill_elem);
	~Vector();

	void Resize(size_t new_size);
	void Push_back(T elem);
	void Insert(Vector& src, size_t pos);

	T Pop_back();
	T RemoveElem(int pos);
	void Slice(int start_pos, int end_pos);

	T* Begin();
	T* End();
	size_t Size();
	T* Begin() const;
	T* End() const;
	size_t Size() const;

	T& operator[] (const unsigned index);
	T  operator[] (const unsigned index) const;
	Vector& operator=(const Vector& src);
	Vector& operator+= (const Vector& src);
	Vector& operator*= (const unsigned num);
private:
	T* _data;
	size_t _size, _capacity;
};