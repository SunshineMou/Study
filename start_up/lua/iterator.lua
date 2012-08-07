#!/usr/bin/lua

--[[
function list_iter ( t )
    local i = 0 
    local n = table.getn( t )    --返回table中元素的个数；
    return function ()
        i = i + 1
        if 
            i <= n
            then
                return t[i]
            end
        end
end

t = { 10, 20, 30 }
iter = list_iter(t)
while true
    do
        local element = iter()
        if element == nil
            then
                break
            end

print (element)
end

for element in list_iter(t) do
    print(element)
end
--]]

function allwords()
    local line = io.read()
    local pos = 1
    return function()
        while line do
            local s, e = string.find(line, "%w+", pos)
            if s then
                pos = e + 1
                return string.sub(line, s, e)
            else
                line = io.read()
                pos =1
            end
        end
        return nil
    end
end

iter = allwords()
while true
    do
        local element = iter()
        if element == nil
            then
                break
            end

print (element)
end
