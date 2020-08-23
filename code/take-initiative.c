    void get_PutCardList_2(HandCardData &clsHandCardData)
    {
    	
    	clsHandCardData.ClearPutCardList();
     
    	//剪枝：如果能出去最后一手牌直接出
    	CardGroupData SurCardGroupData = ins_SurCardsType(clsHandCardData.value_aHandCardList);
    	//如果能一次性出去且不是四带二，因为主动出牌若手上剩四带二牌的话可以考虑先打一手然后炸，获得双倍积分
    	if (SurCardGroupData.cgType != cgERROR&&SurCardGroupData.cgType!=cgFOUR_TAKE_ONE&&SurCardGroupData.cgType !=cgFOUR_TAKE_TWO)
    	{
    	}
     
    	/*王炸——当前策略只处理王炸作为倒数第二手的优先出牌逻辑，后续版本会在此基础上优化*/
    	if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
    	{
    	}
     
    	//暂存最佳的价值
    	HandCardValue BestHandCardValue;
    	BestHandCardValue.NeedRound = 20;
    	BestHandCardValue.SumValue = MinCardsValue;
    	//我们认为不出牌的话会让对手一个轮次，即加一轮（权值减少7）便于后续的对比参考。
    	BestHandCardValue.NeedRound += 1;
     
    	//暂存最佳的组合
    	CardGroupData BestCardGroup;
     
    	//带出去的牌
    	int tmp_1 = 0;
    	int tmp_2 = 0;
    	int tmp_3 = 0;
    	int tmp_4 = 0;
        //优先处理三牌、飞机等牌
    	for (int i = 3; i < 16; i++)
    	{		
    	}
    	//这部分出牌处理放到循环外
    	if (BestCardGroup.cgType == cgTHREE_TAKE_ONE)
    		{
     
    		}
    	else if (BestCardGroup.cgType == cgTHREE_TAKE_TWO)
    		{
     
    		}
    	else if (BestCardGroup.cgType == cgTHREE_TAKE_ONE_LINE)
    		{
     
    		}
    	else if (BestCardGroup.cgType == cgTHREE_TAKE_TWO_LINE)
    		{
     
    		}
    		
     
    	//次之处理当前价值最低的牌，现在不必再考虑这张牌可能被三牌带出等情况
    	for (int i = 3; i < 16; i++) 
    	{
    	}
    	//如果没有3-2的非炸牌，则看看有没有单王
    	if (clsHandCardData.value_aHandCardList[16] == 1 && clsHandCardData.value_aHandCardList[17] == 0)
    	{		
        }
    	if (clsHandCardData.value_aHandCardList[16] == 0 && clsHandCardData.value_aHandCardList[17] == 1)
    	{
    	}
    	//单王也没有，出炸弹
    	for (int i = 3; i < 16; i++)
    	{
    	}
    	
    	//异常错误
    	clsHandCardData.uctPutCardType = get_GroupData(cgERROR, 0, 0);
    	return;
     
    }