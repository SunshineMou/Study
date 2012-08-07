#!/usr/bin/lua
        --这个lua文件主要体现了闭包的操作！
function newcounter()
    local i = 0;
    return function()
        i=i+1;
        return i;
    end
end

c1 =newcounter();
print(c1());
print(c1());

c2=newcounter();
print(c2());
print(c1());
print(c2());
