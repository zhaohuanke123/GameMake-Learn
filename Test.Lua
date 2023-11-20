controller = {}

controller.init = function(...)
    t = {...}
    for i, v in ipairs(t) do
        print(i, v)
    end
    print("controller:init")
end

controller.update = function()
    print("controller:update")
end

controller.destroy = function()
    print("controller:destroy")
end

meta2 = {
    __tostring = function(t)
        return "meta2"
    end
}

mtable = {
    __index = function(t, k)
        print("index", k)
        return "index"
    end,
    __newindex = function(t, k, v)
        print("newindex", k, v)
    end,
    __tostring = function(t)
        return "mtable"
    end
}

test = {id= 1,name = "test"}
test1 = {id= 1,name = "test"}
test2 = {id= 1,name = "test"}
test3 = {id= 1,name = "test"}

print(collectgarbage("count"))
test = nil
test1 = nil
test2 = nil
test3 = nil
collectgarbage("collect")
print(collectgarbage("count"))