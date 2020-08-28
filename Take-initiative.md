# 主动出牌想法策略研究
主动出牌的策略按照优先级大体可以分为三类：<br/>
【一】能直接一手牌出去，优先出。<br/>
【二】两手牌出去且有绝对大牌，先出绝对大牌。<br/>
【三】出一手牌使得接下来自己手牌价值最大化。<br/>
对于【一】：
```
    //剪枝：如果能出去最后一手牌直接出
    	CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
    	//如果能一次性出去且没有炸弹，因为有炸弹的话权值可能会更大
    	if (SurCardGroupData.cgType != cgERROR&&!HasBoom(clsHandCardData.value_aHandCardList))
    	{
    			Put_All_SurCards(clsHandCardData, SurCardGroupData);
    			return;
    	}
```
然后是【二】：目前我们暂时不考虑记牌功能，所以绝对大牌只支持王炸，以后在这里可以做更多智能的处理。 <br/>
```
/*王炸——当前策略只处理王炸作为倒数第二手的优先出牌逻辑，后续版本会在此基础上优化*/
	if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
	{
 
		clsHandCardData.value_aHandCardList[17] --;
		clsHandCardData.value_aHandCardList[16] --;
		clsHandCardData.nHandCardCount -= 2;
		HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
		clsHandCardData.value_aHandCardList[16] ++;
		clsHandCardData.value_aHandCardList[17] ++;
		clsHandCardData.nHandCardCount += 2;
		if (tmpHandCardValue.NeedRound == 1)
		{
			clsHandCardData.value_nPutCardList.push_back(17);
			clsHandCardData.value_nPutCardList.push_back(16);
			clsHandCardData.uctPutCardType = get_GroupData(cgKING_CARD, 17, 2);
			return;
		}
	}
```
接下来就是第三步， 就是我们选择打出一手牌尽量使得接下来自己手牌价值最大化。 <br/>
与被动出牌不一样的是，主动出牌我们没有限制条件，我也尝试过全部枚举，不过时间消耗肯定是爆炸的。于是我定制了一个基本的出牌优先级策略：<br/>
①三带一优先打出，因为这种牌型可以把小牌带出。其实这里对比较大的三带一不是很公平，后续版本可以在此处做分支处理，比如说三带一的话只循环到H2SO3，剩下的先不着急打出。<br/>
```
for (int i=3; i<16;i++){
	//2.0版本策略主动出牌不拆分炸弹，我就不打四带二，因为浪
	if (clsHandCardData.value_aHandCardList[i] != 4){
		//出三带一
		if (clsHandCardData.value_aHandCardList[i] > 2){...}
		//出三带二
		if (clsHandCardData.value_aHandCardList[i] > 2){...}
		//出四带二
		if (clsHandCardData.value_aHandCardList[i] > 3){
			//2.0版本策略主动出牌不拆分炸弹，我就不打四带二，因为浪
		}
		//出三带一单连
		if (clsHandCardData.value_aHandCardList[i] > 2){...}
		//出三带一双连
		if (clsHandCardData.value_aHandCardList[i] > 2){...}	
	}
}
id (BestCardFroup.cgType == cgTHREE_TAKE_ONE){...}
else if (BestCardFroup.cgType == cgTHREE_TAKE_TWO){...}
else if (BestCardFroup.cgType == cgTHREE_TAKE_ONE_LINE){...}
else if (BestCardFroup.cgType == cgTHREE_TAKE_TWO_LINE){...}
```
若可以出这几种牌型，选择一种价值最高的打出。因为要枚举所有的牌，所以在循环外根据最佳策略进行出牌处理。<br/>
②没有上述牌型后，优先处理当前最小的一张牌。若是该牌有四张，先不处理。<br/>
```
//次之处理当前价值最低的牌，现在不必再考虑这张牌可能被三牌带出等情况
for (int i=3;i < 16;i++){
	if (clsHandCardData.value_aHandCardList[i] != 0 && clsHandCardData.value_aHandCardList[i] != 4){
		//出单牌
		if (clsHandCardData.value_aHandCardList[i] > 0){...}
		//出对牌
		if (clsHandCardData.value_aHandCardList[i] > 1){...}
		//出单顺
		if (clsHandCardData.value_aHandCardList[i] > 0){...}
		//出三牌
		if (clsHandCardData.value_aHandCardList[i] > 2){...}
		//出双顺
		if (clsHandCardData.value_aHandCardList[i] > 1){...}
		//出三顺
		if (clsHandCardData.value_aHandCardList[i] > 2){...}
	}
}
```
放在if里是因为若此时i有值那么必须要返回一个结果<br/>
```
if (BestCardGroup.cgType == cgERROR){...}
else if (BestCardGroup.cgType == cgSINGLE){...}
else if (BestCardGroup.cgType == cgDOUBLE){...}
else if (BestCardGroup.cgType == cgTHREE){...}
else if (BestCardGroup.cgType == cgSINGLE_LINE){...}
else if (BestCardGroup.cgType == cgDOUBLE_LINE){...}
else if (BestCardGroup.cgType == cgTHREE_LINE){...}
else if (BestCardGroup.cgType == cgTHREE_TAKE_ONE){...}
else if (BestCardGroup.cgType == cgTHREE_TAKE_TWO){...}
else if (BestCardGroup.cgType == cgTHREE_TAKE_ONE_LINE){...}
else if (BestCardGroup.cgType == cgTHREE_TAKE_TWO_LINE){...}
return;
```
这里出牌处理就放在循环内了，因为当确定了这个i值后无论如何都是要打出一手牌的，且打完牌就可以return了。
③如果没有非炸牌，那么看看有没有单王，如果有，可以出。
```
if (clsHandCardData.value_aHandCardList[16] == 1 && clsHandCardData.value_aHandCardLIst[17] == 0){
	clsHandCardData.value_nPutCardList.push_back(16);
	clsHandCardData.uctPutCardType = get_GroupData(cgSINGLE,16,1);
	return;
}
if clsHandCardData.value_aHandCardList[16] == 0 && clsHandCardData.value_aHandCardLIst[17] == 1){
	clsHandCardData.value_nPutCardList.push_back(17);
	clsHandCardData.uctPutCardType = get_GroupData(cgSINGLE,17,1);
	return;
}
```
④单王也没有，出炸弹。
```
//单王也没有，出炸弹
for (int i=3;i<16;i++){
	if (clsHandCardData.value_aHandCardList[i] == 4){
		clsHandCardData..value_nPutCardList.push_back(i)
		clsHandCardData..value_nPutCardList.push_back(i);
		clsHandCardData..value_nPutCardList.push_back(i);
		clsHandCardData..value_nPutCardList.push_back(i);
		
		clsHandCardData.uctPutCardType = get_GroupData(cgBOMB_CARD,i,4);
		
		return;
	}
}
```
这里可能有人会想，需不需要再加上炸弹也没有，出王炸呢？其实不存在的，因为如果你真的没牌打了就剩王炸了，早在前面剪枝部分就处理了。<br/> 
所以如果走到这里都没有返回的话，肯定是出现错误了。<br/>

