#!/usr/bin/lua
 days = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"}
 revDays ={}
 for i,v in ipairs(days) do
     revDays[v] = i
 end
 x = "Sunday"
 print(revDays[x])
