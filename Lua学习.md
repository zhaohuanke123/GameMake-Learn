语言内置模式匹配；

闭包(closure)；

函数也可以看做一个值；

提供多线程（协同进程，并非操作系统所支持的线程）支持；


# 数据类型

number 

string

boolean

nil

function

table

userdata

thread


ipairs 和 pairs 区别


# 闭包

函数内返回函数

向上寻找上值


# 表 table 


# 大G表

总表，也是一个Table（所有变量存储其中）


# 协程


# 元表

```lua
co = coroutine.create(function()
    while true do
        print("coroutine")
        coroutine.yield()
    end
end)

coroutine.resume(co)
```

# 实现面向对象

使用表 表现 类的特性


使用 .调用函数 和 : 调用函数区别

：默认 传入 self


## 封装

```lua
Object = {}
Object.id = 0

function Object:new()
    local o = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

local o = Object:new()
print(o.id)
```

## 继承

```lua
function Object:subClass(className)
    _G[className] = {}
    local class = _G[className]
    self.__index = self

    setmetatable(class, self)
end

Object:subClass("Test" )
Test.mm = function()
    print("123123")
end

t =  Test:new()
t.mm()

Test:subClass("Test2")
t2 = Test2:new()
t2.mm()

```


# 多态

```lua
Object = {}
Object.id = 1

function Object:new()
    local o = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Object:subClass(className)
    _G[className] = {}
    local class = _G[className]
    self.__index = self
    class.base = self -- 保存父类
    setmetatable(class, self)
end

Object:subClass("Test" )

function Test:ctor()
    print("Test:ctor")
end

Test:subClass("Test2")

function Test2:ctor()
    self.base.ctor(self) -- 调用父类的构造函数，这里一定要用 . 而不是 :，然后传入 self
    print("Test2:ctor")
end

t = Test2:new()
t:ctor()
```


# 内存回收

```lua
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
```

有自动GC的机制
