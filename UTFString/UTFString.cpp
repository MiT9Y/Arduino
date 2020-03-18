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

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include <UTFString.h>

UTFString::UTFString(const char *val ){
	if (val == NULL) val = (char*)"";
	getBuffer( _len = strlen(val) );
	if (_str != NULL) {
		strcpy(_str, val);
		_UTFlen = getUTFLen();
	}
}

UTFString::UTFString(const String &val){
	String _local = val;
	getBuffer(_len = _local.length());
	if (_str != NULL) {
		strcpy(_str, &_local[0]);
		_UTFlen = getUTFLen();
	}
}

inline void UTFString::getBuffer(unsigned int maxStrLen){
	_str = (char *) malloc(maxStrLen + 1);
	if (_str == NULL) _len = 0;
}

word UTFString::getNextIndex(word i) {
	if (i >= _len) return 0;
	if ( (128&( (byte) *(_str+i) )) == 0 ) return i+1;	
	if ( (192&( (byte) *(_str+i) )) == 192 ) return i+2;
	if ( (224&( (byte) *(_str+i) )) == 224 ) return i+3;
	if ( (240&( (byte) *(_str+i) )) == 240 ) return i+4;
	while ( ( (byte) *(_str+i) >> 6 ) == 2 ) {
		i ++;
	}
	return i;
}

String UTFString::charAt(word index){
	word F; word L;
	getArrIndex(&F,&L,index);
	if (L<F) return "";
	char * res = (char *) malloc(L-F+1);
	if (res == NULL) return "";
	memcpy(res, _str+F, L-F);
	res[L-F] = 0;
	return res;
}

String UTFString::substring(word beginIndex) {
	return substring(beginIndex, _UTFlen);	
}

String UTFString::substring(word beginIndex, word endIndex) {
	if (beginIndex>endIndex) return "";
	word F; word L;
	if (beginIndex<1) getArrIndex(&F,NULL,1); else getArrIndex(&F,NULL,beginIndex);
	if (endIndex>_UTFlen) getArrIndex(NULL,&L,_UTFlen); else getArrIndex(NULL,&L,endIndex);
	char * res = (char *) malloc(L-F+1);
	if (res == NULL) return "";
	memcpy(res, _str+F, L-F);
	res[L-F] = 0;
	return res;	
}

void UTFString::concat (String * _stArr, byte _size){
	String _sumStr = "";
    for (byte i = 0; i < _size; i++) _sumStr += _stArr[i];
	getBuffer(_len = _sumStr.length());
	if (_str != NULL) {
		strcpy(_str, &_sumStr[0]);
		_UTFlen = getUTFLen();
	}
}

// return 0 if not found. 
word UTFString::indexOf( const String &s2 ){return indexOf( s2, 1 );}
word UTFString::indexOf( const String &s2, word fromIndex ){
	String _local = s2;
	if ( fromIndex > _UTFlen || _UTFlen == 0 ) return 0;
	word F;
	getArrIndex(&F,NULL,fromIndex);
	const char *theFind = strstr( &_str[F], &_local[0] );
	if ( theFind == NULL ) return 0;
	if (theFind == _str) return 1;
	word Fadd = (word) (theFind - _str);
	word len = 0;
	word i = getNextIndex(0);
	while (i>0) {
		len++;
		if (i == Fadd) return len+1;
		i = getNextIndex(i);
	}
	return 0; // pointer subtraction
}

// return 0 if not found. 
word UTFString::lastIndexOf( const String &s2 ){ return lastIndexOf(s2, 1);}
word UTFString::lastIndexOf( const String &s2, word fromIndex ){
  word res = 0;
  word i = _UTFlen-fromIndex+1;
  if ( fromIndex < 1 || _UTFlen == 0 || i > _UTFlen) return res;
  word found = indexOf(s2);
  if (found == 0 || found>i) return res;
  res = found; 
  while (found>0){
	found = indexOf(s2,found+1);
	if (found>i) return res;
	if (found == 0) return res;
	res = found;
  }
}

void UTFString::replace(const String & match, const String & replace) {
	String _local = _str;
	_local.replace(match,replace);
	getBuffer(_len = _local.length());
	if (_str != NULL) {
		strcpy(_str, &_local[0]);
		_UTFlen = getUTFLen();
	}	
}

void UTFString::getArrIndex(word *F, word *L,word i) {
	if (F) *F = 1;
	if (L) *L = 0;
	if (i<1||i>_UTFlen) return;
	word len = 0;
	word b = 0; word e = getNextIndex(b);
	while (e>0){
		len++;
		if (len == i) break;
		b = e; e = getNextIndex(b);
	}
	if (F) *F = b;
	if (L) *L = e;
}

word UTFString::getUTFLen() {
	word len = 0;
	word i = getNextIndex(0);
	while (i>0){
		len++;
		i = getNextIndex(i);
	}
	return len;
}