### 设计模式

#### 创建型模式：

> 描述怎样创建对象，将对象的创建和使用分离

1. 单例 [singleton](/singleton)，一个类只能实例化一个对象
2. 原型 [prototype](/prototype)，根据基类指针拷贝出派生类对象
3. 简单工厂 [factory](/factory)，根据名称创建对应的对象，本质是基类指针指向派生类对象实现多态
4. 工厂方法，对象创建不再由工厂类进行，而是交由派生类执行
5. 抽象工厂，一个工厂不只生产一种产品，而是可以生产多种产品
6. 建造型 [builder](/builder)，产品的构造过程和表示是独立的

#### 结构性模式：

> 怎样将对象按照某种布局组成更大的结构

1. 代理 [proxy](/proxy)，为其他对象提供一个代理以控制该对象的访问
2. 适配器 [adaptor](/adaptor)，将类的接口转为另一个接口，使得不相容的接口可以一起工作
3. 桥接 [bridge](/bridge)，将抽象和实现分离，用组合关系代替继承关系
4. 装饰 [decorator](/decorator)，动态地给对象增加功能
5. 外观 [facade](/facade)，为多个子系统提供统一的接口
6. 享元 [flyweight](/flyweight)，将对象共享以支持对象的复用
7. 组合 [composite](/composite)，将对象组合成树状层次结构

#### 行为型模式

> 对象间协作完成单个对象无法完成的任务

1. 模版方法 [template_method](/template_method)，定义一个操作的算法骨架，按照某种顺序调用其包含的基本方法
2. 策略 [strategy](/strategy)，将每个算法封装起来，使得可以相互替换
3. 命令 [command](/command)，将请求封装为对象，使得发出请求和接收请求分开
4. 责任链 [responsibility](/responsibility)，把请求从链中的一个对象转移到下一个对象
5. 状态 [state](/state)，对象内部状态改变时改变其行为
6. 观察者 [observer](/observer)，当一个对象发生改变时，将改变的通知发给其他的对象
7. 中介者
8. 迭代器 [iterator](/iterator)，顺序访问对象中的数据而不暴露对象的内部表示
9. 访问者
10. 备忘录
11. 解释器

### 参考资料

[图说设计模式](https://design-patterns.readthedocs.io/zh-cn/latest/index.html)

其他代码仓库：

1. https://github.com/FengJungle/DesignPattern
2. https://github.com/youngyangyang04/DesignPattern


