# AssetBundle打包加载卸载

1项目相关
很多小伙伴工作很多年了，也不知道AssetBundle怎么打包的，怎么加载以及卸载的，这里我为大家总结了下用法，附上源码工程，可以看明白之后写在自己简历上，增加亮点。代码里做了详细的注解，可以自行研究。

👉课程地址[点击查看](https://ajngh.xet.tech/s/3S9svg)
源工程下载

WindAssetBundle.rar**(125.3 MB)**

注意事项：

1.1.1打出的ab资源在工程同级的AssetBundle下

1.1.2可以无缝切换编辑器和AB加载方式

1.1.3注意AB模式下，改完资源记得Tools/ResBuild一下

1.1.4支持同步异步等方式

1.1.5具体的打包配置在BuildSetting.xml里配置即可，具体精细到文件还是文件夹都可以，因为是xml这个可以给资源策划去配置，不用程序关心，专心做业务逻辑。

不断轮询确保及时卸载不用的Ab

```csharp
public void LateUpdate()
        {
            if (m_NeedUnloadList.Count == 0)
                return;

            while (m_NeedUnloadList.Count > 0)
            {
                ABundle bundle = m_NeedUnloadList.First.Value;
                m_NeedUnloadList.RemoveFirst();
                if (bundle == null)
                    continue;

                m_BundleDic.Remove(bundle.url);

                if (!bundle.done && bundle is BundleAsync)
                {
                    BundleAsync bundleAsync = bundle as BundleAsync;
                    if (m_AsyncList.Contains(bundleAsync))
                        m_AsyncList.Remove(bundleAsync);
                }

                bundle.UnLoad();

                //依赖引用-1
                if (bundle.dependencies != null)
                {
                    for (int i = 0; i < bundle.dependencies.Length; i++)
                    {
                        ABundle temp = bundle.dependencies[i];
                        UnLoad(temp);
                    }
                }
            }
        }
```


加载要确保打包没有循环依赖即可

2面试相关

明确概念

2.1.1Asset是什么？
游戏中具体的资源，像texture，mesh，material，shader，script等，实实在在的游戏项目文件夹中所需要堆放的资源。比如，var obj = Resource.Load`<GameObject>`("Prefabs/testItem")，这个obj就是Asset。

2.1.2GameObject是什么？
var gameItem= Instantiate(obj)，这个gameItem就是可以存在于游戏的实际场景中（这个比较简单，不多说了）。GameObject是游戏中实际使用的对象（就是你会在屏幕中实际看到的），是由Asset实例化后的对象。本质上其实还是Asset的衍变，是对部分Asset的引用和复制出来的新东西，其本质还是Asset。

2.1.3AssetBundle是什么？
由上述可知，我们在游戏中生成实际的物体，需要Asset。而Asset，比如一张图片，也是一个Asset，实际大小1M，游戏中这种图片很多，那就轻轻松松几百M，几个G的Asset，都是很有可能的。作为程序员，对于这种“原汁原味”拿过来肯定不行。比如我们工作中把文件什么的发给同事的时候都知道压缩一下，可以传输的过程中小一些。当然了，我们在游戏开发中使用Asset，也是需要类似的。于是，就推出了AssetBundle这一概念。当然我们推出AssetBundle，远不止压缩这一需求。但是你需要知道，主要是为了更好的传输，还有比如减少资源大小，利于网络那边的传输，方便加载。
简而言之，AssetBundle就是为了让游戏项目中大量Asset适应实际游戏运行时而被压缩后的一种二进制文件。

打包策略
 在打包的时候，我们需要对包的大小和数量进行一个平衡，所有资源打成一个包，一个资源打一个包，都是比较极端的做法，他们的问题也很明显，更多情况下我们需要灵活地将他们组合起来
    打成一个包的缺点是加载了这个包，我们不需要的东西也会被加载进来，占用额外内存，而且不利于热更新
    打成多个包的缺点是，容易造成冗余，首先影响包的读取速度，然后包之间的内容可能会有重复，且太多的包不利于资源管理
    哪些模块打成一个包，哪些模块打成多个包，需要根据实际情况来，例如游戏中每个怪物都需要打成一个包，因为每个怪物之间是独立的，例如游戏的基础UI，可以打成一个包，因为他们在各个界面都会出现

2.1资源依赖
在我们打包的时候，将两个资源打包成单独的包，那么两个资源所共用的资源，就会被打包成两份，这就造成了冗余，所以我们需要将公共资源抽出来，打成一个Bundle，然后后面两个资源，依赖这个公共包，那么还有另外一种方法，就是把它们三打成一个包，但这不利于后期维护。
![](https://cdn.nlark.com/yuque/0/2023/png/39140812/1699694441409-6bdb3d86-18f9-4a66-9edb-a6fbb5cf39b8.png?x-oss-process=image%2Fformat%2Cwebp%2Fresize%2Cw_863%2Climit_0)

此时xml配置就需要有人去维护，一般是根据项目的逻辑划分的，毕竟逻辑模块天然就独立开，尽可能的减少依赖

2.2循环依赖
什么是循环依赖呢，就是A包依赖B包，B包里的资源也依赖A，这样加载的时候就死循环了，其实在构建ab包的时候就应该发现这样的问题
可以打包时候详细记录里面asset的情况，打的过程中就通过asset级别的检测，检查是否所在包和别的包有循环依赖情况。

2.3依赖丢失
当我们的Bundle之间有了依赖之后，就不能像前面那样简单地直接Load对应的Bundle了，我们需要把Bundle所依赖的Bundle先加载进来，如果BundleB依赖BundleA，当我们要加载BundleB的资源时，假设BundleA没有被加载进来，或者已经被Unload了，那么BundleB依赖BundleA的部分就会丢失。
如下所示
![](https://cdn.nlark.com/yuque/0/2023/png/39140812/1699694706997-d550656b-c6eb-4676-b38b-62ec68142dcb.png?x-oss-process=image%2Fformat%2Cwebp%2Fresize%2Cw_525%2Climit_0)

![](https://cdn.nlark.com/yuque/0/2023/png/39140812/1699694706986-b19b9c6b-9af1-4344-937a-bc75ab8cae61.png?x-oss-process=image%2Fformat%2Cwebp%2Fresize%2Cw_471%2Climit_0)

2.4公用资源常驻方案
比如一些公用图集，font字体等公用的东西，可以适当的在ab加载之后常驻内存（只要在合理的范围内就可以），这样能避免卸载公用的导致频繁用又去加载这样的消耗。优化是一个平衡的过程，没有一成不变的方案，根据项目去取舍。

2.5压缩方式推荐Lz4

2.5.1压缩方式（Lz4和Lzma）：现在Unity主推Lz4（也就是ChunkBased，BuildAssetBundleOptions.ChunkBasedCompression），Lz4非常快，大概是Lzma的十倍左右，但是平均压缩比例会比Lzma差30%左右，即包体可能会更大些。Lz4的算法开源。
Lzma基本可以不用了，因为Lzma解压和读取速度都会非常慢，并且占大量的内存，因为不是ChunkBased，而是Stream，也就是一次全解压出来。而ChunkBased可以一块一块解压，每次解压可以重用之前的内存，减少内存的峰值。

2.5.2大小和数量：AssetBundle分两部分，一部分是头（用于索引），一部分是实际的打包的数据部分。如果每个Asset都打成一个AssetBundle，那么可能头的部分比数据还大。

2.6Resource
Resource文件夹里的内容被打进包的时候会做一个红黑树（R-B Tree）用做索引，即检索资源到底在什么位置。所以Resource越大，红黑树越大，它不可卸载，并在刚刚加载游戏的时候就会被一直加在内存里，极大的拖慢游戏的启动时间，因为红黑树没有分析和加载完，游戏是不会启动的，并造成持续的内存压力。所以建议不要使用Resource，使用AssetBundle。

2.7卸载时机和方式
AssetBundle的释放：
AssetBundle.Unload(flase)是释放 AssetBundle 文件的内存镜像，不包含Load创建的Asset内存对象。
AssetBundle.Unload(true)是释放那个 AssetBundle 文件内存镜像和并销毁所有用Load创建的Asset内存对象。
一般来说，切场景的时候最好是用AssetBundle.Unload(true)的方式，卸载的彻底一些，要不然随着游戏时长，内存垃圾越来越多。
对于用户来说，如果选择 AssetBundle.Unload(true)，用户必须确保 Bundle 中已经加载的 资源 是没有被引用的，否则就会发生 资源丢失。
如果选择 AssetBundle.Unload(false)，用户就要承担起卸载 已加载资源 的责任，如果处理不当，就可能造成 资源重复，如下图：
![](https://cdn.nlark.com/yuque/0/2023/png/39140812/1699704065869-9fa9cb7f-ee76-4a4a-9e73-8396de301129.png?x-oss-process=image%2Fformat%2Cwebp%2Fresize%2Cw_449%2Climit_0)

最后，Unity提供了一个 Resources.UnloadUnusedAssets 接口帮助我们销毁没有任何引用的 野资源，不过这个函数会扫描全部对象，开销较大，一般只在 切场景 时调用。

2.8资源的复制和引用
你 Instaniate一个Prefab，是一个对Assets进行Clone(复制)+引用结合的过程，GameObject transform 是Clone是新生成的。其他mesh / texture / material / shader 等，这其中些是纯引用的关系的，包括：Texture和TerrainData，还有引用和复制同时存在的，这个一定要知道，面试可能考。

![微信图片_20231111204505_副本.png](https://cdn.nlark.com/yuque/0/2023/png/39140812/1699707325734-bddb4437-9a98-4f71-9fd0-260b4f2f1654.png?x-oss-process=image%2Fformat%2Cwebp%2Fresize%2Cw_722%2Climit_0)

打包的时候每个ab生成的.manifest文件没有必要留下了，只需要总的那个即可
