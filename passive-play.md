# 对于被动出牌的研究
算法思路：若存在手牌17（大王）和16（小王），那么先去除这两张牌<br/>
然后通过get_HandCardValue获取剩余轮次。<br/>
再回溯到原有状态。若只剩一手，则打出王炸。<br/>
出牌的操作也很简单，将需要打出的牌进入clsHandCardData.value_nPutCardList数组，且通过get_GroupData函数获取类型结构再赋值给手牌类以及游戏全局类相应的成员变量。当确定好出牌策略后，直接return。因为被动出牌的分支只会走一个，为了节约时间，所以每个分支里都有return，若没有走入任何分支则视为错误数据。<br/>
```
else if （clsGameSituation.uctNowCardGroup.cgType == cgKING_CARD）{
	clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
	return;
}
```
若不出牌，我们只更新自己手牌类型就好了。若出牌时，不但要更新自己手牌信息，也要更新游戏全局类里面的当前出牌信息。不过我更推荐后期嵌入的时候通过服务器来获取当前出牌的信息。比如我的测试函数里会加上：<br/>
```
if (arrHandCardData[indexID].uctPutCardType.cgType != cgZERO){
	clsGameSituation.nCardDroit = indexID;
	clsGameSituation.uctNowCardGroup = arrHandCardData[indexID].uctPutCardType;
}
```
