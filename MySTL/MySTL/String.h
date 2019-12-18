class String
{
public:
	String();
	String(const String& src);
	String(const char src[]);
	String(size_t len, char fill_elem);
	~String();

	size_t Lenght();
	size_t Lenght() const;

	void Resize(size_t new_size);

	char* C_string();
	char* C_string() const;


	String& operator=(const String& src);
	String& operator=(const char src[]);
	String& operator+=(const String& a);
	String& operator+=(const char a[]);
	String& operator*=(const unsigned m);

	char& operator[](const unsigned index);
	char operator[](const unsigned index) const;

	friend String operator+(const String& a, const String& b);
	friend String operator+(const String& a, const char b[]);
	friend String operator+(const char a[], const String& b);

	friend String operator*(const String& a, const unsigned b);
	friend String operator*(const unsigned a, const String& b);
private:

	char* _data;
	size_t _len, _capacity;
	bool _is_null;
};