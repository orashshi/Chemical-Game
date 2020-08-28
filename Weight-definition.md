#关于权值定义模块的分析
首先，我想应该要有出牌轮次的定义。我们要尽量使得出牌轮次少一些。还是那句话，所以对于牌型，大家是公平的。你组成这种牌型的几率低，但你管别人的几率也低。你若想出去，还是要用其他的牌抢占先手再打出，所以这种牌型不会给你带来抢占出牌权的收益。那么他的好处或许是能让你快速的出完牌，减少出牌轮次。<br/>
然后就是牌的基础价值定义，牌的价值一定有正有负，我也是经过一些测试及计算，**确定了价值为0的位置是亚硫酸(H2SO3)**。<br/>
我们有60种牌型，从值域来说是3~63。**那么属于最中间的位置是亚硫酸(H2SO3)**。还有就是我们打斗地主的时候经常管10以上的牌称作带“人”的牌（因为JQK有人图案）。我们认为带“人”的牌都是干部，是可以管别人的。<br/>
或许有人会说，王比其他牌型少，且人家若成了王炸又不可能拆开出。但实际玩牌的时候王牌管单出现的几率和其他牌差不多。大家的拆分选择可以认为近似公平的。至于牌少的问题，你想想你一局游戏实际打单牌的次数也没多少次。况且，基础价值是应用于所有类型的牌值的。但他不能说明一切问题。他只是表示当你的牌值大于10以上，你管上别人的概率高，反之，你被管的概率高。<br/>
根据这个思路，我们暂定单和三等牌型的价值就是这个基础价值。也就是的基础价值是-22  大王的基础价值是12<br/>
根据这个基础价值，我们便得出控手（轮次）的价值。因为最大负牌值是-7，所以控手价值是7，这个应该不难理解把。因为你若想打出一个3，你就必须得抢占一次控手机会。然后再打出3。同理，一次控手机会可以出一手牌，所以单个轮次的价值也是7，若你的牌型组合价值大于7，则认为你这种牌型可以创造一个轮次，举个简单的例子王炸。<br/>
最后说一下炸弹及王炸，炸弹无负价值且+一个轮次7，因为我们认为炸弹大概率能抢占一局轮次。而炸弹及王炸没有正价值收益缩减的原因是处于信仰把，尽量的不要拆分。也符合我们人性。我们都是把炸弹、王炸看成最重要的。<br/>x`
还有，在此之前我有想过权值定义取不拆分和拆分的最大价值。比如说3A带俩2，那么其实俩2的价值也很高，后期很有可能拆开打。但是最后因为引入了手牌轮次参数，所以不考虑拆分价值了。不然四带二的价值爆炸。<br/>
## 下面给出目前暂定的定义方案：
####0.由于新策略引入手牌轮次参数，所以不再考虑拆分价值。<br/>
####1.牌力基础价值：我们认为10属于中等位置，即<10单牌价值为负，大于10的单牌价值为正<br/>
####2.控手的价值定义：我们认为一次控手权可以抵消一次手中最小牌型，最小牌型（3）的价值为-7，即我们定义一次控手权的价值为7<br/>
####3.单牌的价值定义：该牌的基础价值<br/>
####4.对牌的价值定义：我们认为对牌与单牌价值相等（均可以被三牌带出）故其价值为该牌的基础价值<br/>
####5.三牌的价值定义：<br/>
  三不带：     该牌的基础价值<br/>
  三带一：     我们认为通常带出去的牌价值一定无正价值故其价值为该牌的基础价值<br/>
  三带二：     我们认为通常带出去的牌价值一定无正价值故其价值为该牌的基础价值<br/>
####6.四牌的价值定义：<br/>
  炸弹：       我们认为炸弹会享有一次控手权利且炸弹被管的概率极小，故其无负价值，非负基础价值+7<br/>
  四带二单：   我们认为四带二单管人与被管的概率极小，故其无负价值，其价值为非负基础价值/2（该值最大为6小于一个轮次7)<br/>
  四带二对：   我们认为四带二对管人与被管的概率极小，故其无负价值，其价值为非负基础价值/2（该值最大为6小于一个轮次7)<br/>
####7.王炸的价值定义：已知炸2价值为15-3+7=19分，故王炸价值为20分。<br/>