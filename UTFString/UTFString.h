/*MIT License

Copyright (c) 2020 Chmyhov_Dmitry(chmihovd@yandex.ru)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef UTFString_H
#define UTFString_H

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

class UTFString
{
  public:
	// constructors
	UTFString(const char *val = "");
	UTFString(const String &val);	
	~UTFString(){/*free(_str); _len = _UTFlen = 0;*/};
	
	// operators
	operator const char *() {return _str;}
	
	// methods
	const word length() const {return _UTFlen;}
	void concat (String * _stArr, byte _size = 1);	
	String charAt(word index);
	String substring(word beginIndex);
    String substring(word beginIndex, word endIndex);
	word indexOf( const String &str );
    word indexOf( const String &str, word fromIndex );
	word lastIndexOf( const String &str );
    word lastIndexOf( const String &str, word fromIndex );
	void replace( const String & match, const String & replace );
	
  protected:
    char * _str = (char*)"";
	word _len = 0;
	word _UTFlen = 0;
	void getBuffer(unsigned int maxStrLen);
	
  private:
	//function
    word getNextIndex(word i);
	void getArrIndex(word *F, word *L ,word i); //First & Last byte index char of string
	word getUTFLen();
};

#endif
