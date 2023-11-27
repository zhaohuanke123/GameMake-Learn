# 游戏框架

![1700551277335](image/MMO/1700551277335.png)

渲染3D模型在UI上

Render Texture（性能要求不高的场景）

同步：

![1700922705189](image/MMO/1700922705189.png)

# 使用的协议

Google 的 Protocol Buffers（简称为protobuf）是一种用于序列化结构化数据的开源协议。它被设计用于高效、简单、通用的数据交换格式。下面是使用protobuf的一些主要好处：

1. **高效的序列化和反序列化：** Protocol Buffers 是一种二进制协议，相比于一些文本协议（例如 JSON 或 XML），它的序列化和反序列化速度更快，生成的数据包也更小。这对于网络通信和存储是非常重要的，尤其是在资源受限的环境中。
2. **跨语言支持：** Protobuf 定义了一个数据格式和编译器，支持多种编程语言，包括但不限于 C++, Java, Python, Go, JavaScript 等。这意味着可以在不同的平台和语言之间轻松地共享数据。
3. **版本兼容性：** Protobuf 具有良好的版本兼容性。当你需要对数据结构进行修改时，可以在不破坏现有代码的情况下演化数据结构。新添加的字段可以被旧版本的解析器忽略，这使得系统的升级更加容易。
4. **数据结构定义：** Protobuf 使用一个结构化的描述文件定义数据结构，这种文件以.proto为扩展名。这允许你明确定义消息的结构，包括字段的类型、顺序和默认值等。这对于数据的文档化和维护是非常有帮助的。
5. **代码生成：** Protobuf 通过编译器生成与消息结构对应的代码，包括用于序列化和反序列化的代码以及用于消息访问的代码。这样的自动生成可以减少手动编写和维护序列化和反序列化逻辑的工作。
6. **网络通信：** 由于 Protobuf 的高效性和跨语言支持，它经常用于网络通信协议。在分布式系统中，它可以作为数据交换的标准格式，有助于不同服务之间的通信。

# 进入游戏流程

客户端点击进入游戏

行为：触发事件 OnClickEnter

发送： UserGameEnterRequest （UserService）

服务端收到 UserGameEnterRequest（UserService）

触发：OnGameEnter

发送：UserGameEnterResponse（UserService）

客户端收到 UserGameEnterResponse（UserService）

触发 OnGameEnter

设置 CurrentCharacter

服务端继续发送

继续执行 CharacterEnter （MapManager的Map中）

发送 MapCharacterEnterResponse 给当前Map中的所有Characters（Map）

客户端收到 MapCharacterEnterResponse

~~（触发 OnMapCharacaterEnter （UserService）~~

~~加载场景）~~

触发 OnMapCharacaterEnter （MapService）

遍历所有角色，更新当前角色，添加到CharacterManager的角色列表

检查是否切换地图

# 同步实现流程

> 对象

NEntity （Positon，Direction，Speed）

用于网络传输，承载数据

Entity （position，direction，Speed）

逻辑主体对象，Service和Client各一份

EntityController

控制器

> 流程

玩家操作移动才开始同步

起点：PlayerInputController


TODO


# 传送地图流程


UI 系统 （其他系统的依赖）
