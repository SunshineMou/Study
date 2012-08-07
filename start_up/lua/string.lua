#!/usr/bin/lua

print("Enter a number string:")
line = io.read();
n = tonumber(line);
if n == nil then 
    error(line .. "is not a valid number!");
else
    print(n*2);
end

print (tostring(10) == "10");

print (10 .. "" == "10")
