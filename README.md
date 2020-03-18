# Arduino

## UTF String
This library allows you to work correctly with UTF-8 encoding (1-4 bytes per character).
#### USAGE EXAMPLE
```c
//INIT VARIABLES  
  UTFString UTF_Str = "HELLO МИР!"; Serial.println(String(UTF_Str)+" - LEN="+UTF_Str.length());
  UTF_Str = String(3.52384,6); Serial.println(String(UTF_Str)+" - LEN="+UTF_Str.length());

//CharAt HELLO МИР
//       123456789
  UTF_Str = "HELLO МИР";
  Serial.println(UTF_Str.charAt(0)); // ""
  Serial.println(UTF_Str.charAt(1)); // "H"
  Serial.println(UTF_Str.charAt(8)); // "И"
  Serial.println(UTF_Str.charAt(9)); // "Р"
  Serial.println(UTF_Str.charAt(10));// ""

//SubString
  UTF_Str = "HELLO МИР";
  Serial.println(UTF_Str.substring(1,5));   // "HELLO"
  Serial.println(UTF_Str.substring(7));     // "МИР"
  Serial.println(UTF_Str.substring(0,11));  // "HELLO МИР"
  
//concat
  UTF_Str = "МИР";
  UTF_Str.concat(new String[3] {"HELLO ",String(UTF_Str),"!!!"},3);
  Serial.println(UTF_Str);  // "HELLO МИР!!!"
  
//indexOf, lastIndexOf
  UTF_Str = "HELLO МИР";
  Serial.println(UTF_Str.indexOf("МИР")); //7
  Serial.println(UTF_Str.indexOf("H")); //1
  Serial.println(UTF_Str.indexOf("Р")); //9
  Serial.println(UTF_Str.indexOf("NOT FOUND")); //0
  Serial.println(UTF_Str.indexOf("L")); //3
  Serial.println(UTF_Str.indexOf("L",4)); //4
  Serial.println(UTF_Str.indexOf("L",5)); //0
  Serial.println(UTF_Str.lastIndexOf("L")); //4
  Serial.println(UTF_Str.lastIndexOf("L",7)); //3
  Serial.println(UTF_Str.lastIndexOf("L",8)); //0

//replace
  UTF_Str = "МИР! HELLO МИР.";
  UTF_Str.replace("МИР", "WORLD");
  Serial.println(UTF_Str);//WORLD! HELLO WORLD.
```
