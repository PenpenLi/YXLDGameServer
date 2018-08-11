----------------------��������--------------------------------------
--��ȡָ���ɳ����ϸ����
function GodAnimalSystem_GetAnimalData(EGodAnimal_ObjId)
    local tab = GameServer_pb.Cmd_Cs_QueryGodAnimalDetai();
	tab.dwGodAnimalObjectID = EGodAnimal_ObjId
	Packet_Full(GameServer_pb.CMD_GODANIMAL_DETAIL, tab);

    ShowWaiting()
end
--��ȡָ��δ��õ����޵���ϸ����
function GodAnimalSystem_GetAnimalDataNG(id)
    local tab = GameServer_pb.CMD_GODANIMAL_DETAIL_BYID_CS()
    tab.iGodAnimalID = id
    Packet_Full(GameServer_pb.CMD_GODANIMAL_DETAIL_BYID,tab)

    ShowWaiting()
end
--�ٻ�
function GodAnimalSystem_CallAnimal(id)
   local tab = GameServer_pb.CMD_GODANIMAL_ANIMALSOUL_ACTIVE_CS()
   tab.iAnimalSoulID = id
   g_GodAnimalSystem_callID = id
   Packet_Full(GameServer_pb.CMD_GODANIMAL_ANIMALSOUL_ACTIVE,tab)
end
--����
function GodAnimalSystem_inheritance(acceptPreDwObjectID,passerDwObjectID)
print("passerDwObjectID== "..passerDwObjectID)
print("acceptPreDwObjectID== "..acceptPreDwObjectID)
    local tab = GameServer_pb.Cmd_Cs_ExeGodAnimalInherit()
    tab.dwPasserObjectID = passerDwObjectID
    tab.dwAccepObjectID = acceptPreDwObjectID
    Packet_Full( GameServer_pb.CMD_GODANIMAL_EXEINHERIT, tab)
    ShowWaiting()
end
--��ѯ����֮�������
function GodAnimalSystem_inheritanceData(id,id2) 
    local tab = GameServer_pb.Cmd_Cs_QueryGodAnimalInherit()
    tab.dwAccepObjectID = id
    if(id2 ~= -1)then
        tab.dwPasserObjectID = id2
    end
    Packet_Full( GameServer_pb.CMD_GODANIMAL_QUERYINHERIT, tab )
end
--����
function GodAnimalSystem_TrainMsg(id)
    local tab = GameServer_pb.Cmd_Cs_GodAnimalTrain()
  	tab.dwObjectID = id
  	Packet_Full(GameServer_pb.CMD_GODANIMAL_TRAIN, tab)
  	ShowWaiting()
end
--����
function GodAnimalSystem_GetAnimalStepLevelUp(EGodAnimal_ObjId)
    local tab = GameServer_pb.Cmd_Cs_ExeLevelStepUp()
	tab.dwObjectID = EGodAnimal_ObjId
	Packet_Full(GameServer_pb.CMD_GODANIMAL_EXELEVELSTEPUP, tab)
	ShowWaiting()
end
--���ײ�ѯ
function GodAnimalSystem_GetAnimalStepLevelUpInfo(EGodAnimal_ObjId)
    local tab = GameServer_pb.Cmd_Cs_QueryGodAnimalLevelStep()
    tab.dwObjectID = EGodAnimal_ObjId 
    Packet_Full(GameServer_pb.CMD_GODANIMAL_QUERYLEVELSTEP, tab)
    ShowWaiting()  
end
--��ս
function GodAnimalSystem_GetAnimalActive(EGodAnimal_ObjId)
    local tab = GameServer_pb.Cmd_Cs_GoldAnimalActive()
	tab.dwObjectID = EGodAnimal_ObjId
	Packet_Full(GameServer_pb.CMD_GODANIMAL_ACTIVE, tab)
	ShowWaiting() 
end
--------------------------------------------------------------------------
--��õȽ�
function GodAnimalSystem_getStep(steplevel)
    if steplevel<3 then
        return 1
    elseif steplevel<7 then
        return 2
    elseif steplevel<13 then
        return 3
    elseif steplevel<20 then
        return 4
    else
        return 5
    end
end
--��õȽ׵����ӡ�+��
function GodAnimalSystem_getStepNum(steplevel)
    if steplevel<3 then
        return steplevel
    elseif steplevel<7 then
        return steplevel-3
    elseif steplevel<13 then
        return steplevel-7
    elseif steplevel<20 then
        return steplevel-13
    else
        return 0
    end
end
function GodAnimalSystem_SetSelected(tag)
    local widget = UI_GetBaseWidgetByName("GodAnimalSystem")
    widgetLeft = UI_GetUIImageView(widget, 4524935)
    local showData = UI_GetUIImageView(widgetLeft, 4525191)
    --����
    UI_GetUIButton(showData, 4525100):setButtonEnabled(tag~=4525100)
    --����
    UI_GetUIButton(showData, 4525111):setButtonEnabled(tag~=4525111)
end
--------------------------------------------------
--�������޽���ʱ��Ϸ������������
function GodAnimalSystem_create()
    local i=0
    local animalList = GetLocalPlayer():GetGodAnimalList()
    while i<animalList:size() do
        if animalList[i]:GetBool(EGodAnimal_IsActive) then   
            --�����һ���ɳ������
            GodAnimalSystem_GetAnimalData(animalList[i]:GetInt(EGodAnimal_ObjId))
            --��һ���ɳ����������Ԥ��
            GodAnimalSystem_GetAnimalStepLevelUpInfo(animalList[i]:GetInt(EGodAnimal_ObjId))
            return
        end
        i=i+1
    end
    --���û�г�ս������
    --�����һ���ɳ������
    GodAnimalSystem_GetAnimalData(animalList[0]:GetInt(EGodAnimal_ObjId))
    --��һ���ɳ����������Ԥ��
    GodAnimalSystem_GetAnimalStepLevelUpInfo(animalList[0]:GetInt(EGodAnimal_ObjId))
end
--��������
function GodAniamalSystem_createWidget()
    local widget = UI_CreateBaseWidgetByFileName("UIExport/DemoLogin/GodAnimalSystem.json")
    local function closeFunck(sender,eventType)
       if eventType == TOUCH_EVENT_ENDED then 
          UI_CloseCurBaseWidget(EUICloseAction_FadeOut,0.35)
       end 
    end 
    UI_GetUIButton(widget, 4525445):addTouchEventListener(closeFunck);

    g_isRefreshListView = false
    --�����б�
    GodAnimalSystem_ShowListView(widget)
    GodAnimalSystem_refreshListView(widget)
    --����һ��������Ϊ����--���޸�
    GodAnimalSystem_refreshListViewHL(0,1,widget)

    return widget
end
--�����ɳ��б�
function GodAnimalSystem_refreshListView(widget,animalIDList)
    if animalIDList==nil then
        animalIDList = vector_int_:new_local() 
        GetLocalPlayer():sortGodAnimalWithId(animalIDList)
        print("=============")
    end

    local leftImage = UI_GetUIImageView(widget, 4524938)
    local listView = UI_GetUIListView( leftImage , 4525076)
    listView:removeAllItems()

    local isAddNoCall=false

    --������ʾ���ɳ�-�ѻ��
    local function changeAnimal(sender,eventType)
        if(eventType == TOUCH_EVENT_ENDED) then
            local index = tolua.cast(sender,"ImageView"):getTag()-1400
            local animaldwID = GetLocalPlayer():GetGodAnimalByAnimalId(animalIDList[index]):GetInt(EGodAnimal_ObjId)
            GodAnimalSystem_GetAnimalData(animaldwID)
            GodAnimalSystem_GetAnimalStepLevelUpInfo(animaldwID)
            g_GodAnimalSystem_lastlevel = GetLocalPlayer():GetGodAnimalByAnimalId(animalIDList[index]):GetInt(EGodAnimal_Level)

            GodAnimalSystem_refreshListViewHL(index,animalIDList:size(),widget)
        end
    end
    --������ʾ���ɳ�-δ���
    local function NGchangeAnimal(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            local index = tolua.cast(sender,"ImageView"):getTag()-1400
            GodAnimalSystem_GetAnimalDataNG(animalIDList[index-1])
            GodAnimalSystem_refreshListViewHL(index,animalIDList:size(),widget)
        end
    end
    --��ӵ�е��ɳ�
    for i=0,animalIDList:size()-1,1 do

        local GodAnimal = GetLocalPlayer():GetGodAnimalByAnimalId(animalIDList[i])
        if GodAnimal then
            local GAwidget = UI_GetUIImageView(widget, 111001):clone()
            listView:pushBackCustomItem(GAwidget)
            local GodAnimalData = GodAnimal:getGodAnimalData()
            --name
            local name = GodAnimalData.m_name
        
            local step = GodAnimal:GetInt(EGodAnimal_LevelStep)
            if GodAnimalSystem_getStepNum(step) >0 then
                name = name.."+"..GodAnimalSystem_getStepNum(step)
            end
            UI_GetUILabel(GAwidget, 4525073):setText(name)
            --level
            UI_GetUILabel(GAwidget, 4524975):setText(GodAnimal:GetInt(EGodAnimal_Level))
            --������......
            local step_ = GodAnimalSystem_getStep(step)
            UI_GetUIImageView(GAwidget, 4525071):loadTexture(GodAnimalSystem_getPath("Step",step_))
            --�^��
            UI_GetUIImageView(GAwidget, 4525066):loadTexture(GodAnimalSystem_getPath("iconHero", GodAnimalData.m_ID))
            --ͷ�����
            UI_GetUIImageView(GAwidget, 4525821):loadTexture(GodAnimalSystem_getPath("animalHeadCommon", step_))
            --�Ƿ��ս
            if( GodAnimal:GetBool(EGodAnimal_IsActive) ) then 
                UI_GetUIImageView(GAwidget, 4524976):setVisible(true)
            else
                UI_GetUIImageView(GAwidget, 4524976):setVisible(false)
            end
            --������ʾ���ɳ�
            GAwidget:addTouchEventListener(changeAnimal)
            GAwidget:setTag(i+1400)
        else
            if isAddNoCall == false then
                local NoCall = UI_GetUILayout(widget, 4528178):clone()
                listView:pushBackCustomItem(NoCall)
                isAddNoCall = true
            end
            local NGAwidget = UI_GetUIImageView(widget, 4525386):clone()
            listView:pushBackCustomItem(NGAwidget)   
            local NGGodAnimalData = GetGameData(DataFileGodAniaml,animalIDList[i],"stGodAnimalData")
            --name
            UI_GetUILabel(NGAwidget, 4525393):setText(NGGodAnimalData.m_name)
            --�^��
            UI_GetUIImageView(NGAwidget, 4525391):loadTexture(GodAnimalSystem_getPath("iconHero", NGGodAnimalData.m_ID))
            --��ɫ
            UI_GetUIImageView(NGAwidget, 4525391):addColorGray()
            --ӵ����Ƭ
            local haveNum = GetLocalPlayer():GetPlayerBag():GetItemCountByItemId(NGGodAnimalData.m_changeItemId)
            local allNum = NGGodAnimalData.m_changeNumber

            local percent = haveNum/allNum*100 > 100 and 100
            percent = percent or haveNum/allNum*100

            UI_GetUILoadingBar(NGAwidget, 4525422):setPercent(percent)
            UI_GetUILabel(NGAwidget, 4549318):setText(haveNum.."/"..allNum)
            --������ʾ���ɳ�
            NGAwidget:addTouchEventListener(NGchangeAnimal)
            NGAwidget:setTag((i+1)+1400)
        end
    end
end
--�ɳ��б��Ǳ�ѡ�е�����
function GodAnimalSystem_refreshListViewHL(chooseTag,allNum,widget)
    local leftImage = UI_GetUIImageView(widget, 4524938)
    local listView = UI_GetUIListView( leftImage , 4525076)

    local arra = listView:getItems()
    print("ListView Conut"..arra:count() )

    for i=0,allNum,1 do
        local GodAnimalWidget = listView:getItem(i)
        local image = GodAnimalWidget:getChildByTag(1122)
        if( image ) then
            if i~=chooseTag then
                image:setVisible(false)
            else
                image:setVisible(true)
            end
        end
    end 
end
--�����ȴ�
function GodAnimalSystem_AnimEnd(armature, movementType, movementID)
  if (movementType == LOOP_COMPLETE)then
    if (movementID == "0")then
      if (Random:RandomInt(1, 100) < 15)then
        armature:getAnimation():playWithIndex(1)
      end
    elseif (movementID == "1")then
      armature:getAnimation():playWithIndex(0)
    end
  end
end
--��Ӷ���
function GodAnimalSystem_AddAnimation(widget,animationName)
    if widget:getChildByTag(199) then
        widget:removeChildByTag(199)
    end
    local animalPic = UI_GetUIImageView(widget, 4524948)

    local layout = Layout:create();
    local godanimalanimatrue = GetArmature(animationName)
    godanimalanimatrue:setPosition(ccp(animalPic:getPositionX(),animalPic:getPositionY()))
    godanimalanimatrue:getAnimation():playWithIndex(0) 
    godanimalanimatrue:getAnimation():setMovementEventCallFunc(GodAnimalSystem_AnimEnd) 
    godanimalanimatrue:setAnchorPoint(ccp(0.42,0.42))
    layout:addNode(godanimalanimatrue)
    widget:addChild(layout,5,199)
    animalPic:setVisible(false)
end
--�����ҷ��Ĺ�����������
function GodAnimalSystem_setPublicData(widget,detail)
   --animation 
    local rightImage = UI_GetUIImageView(widget, 4524935)
    --�ɳ�ı�������
    local animalLocal = GetGameData(DataFileGodAniaml,detail.iBaseID,"stGodAnimalData")
    --����
    GodAnimalSystem_AddAnimation(widget,animalLocal.m_animName)
    -------------------------------------------------------------------
    --��ʾ��������
    local function Skillinfo(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then    
            print("tag=="..tolua.cast(sender,"ImageView"):getTag())
            SkillTipForGodAnimal(tolua.cast(sender,"ImageView"):getTag())
        end 
    end
    --����

    local ActiveSkillData = GetGameData(DataFileSkill,detail.iActiveSkillID,"stSkillData")
    local StageSkillData = GetGameData(DataFileSkill,detail.iStageSkillID,"stSkillData")
    print("ActiveSkillData.m_quality=="..ActiveSkillData.m_quality)
    local Active = UI_IconSkillFrame(UI_GetSkillIcon(ActiveSkillData.m_icon), ActiveSkillData.m_quality)
    local Stage = UI_IconSkillFrame(UI_GetSkillIcon(StageSkillData.m_icon), StageSkillData.m_quality)

    UI_GetUIImageView(rightImage, 4525092):removeAllChildren()
    UI_GetUIImageView(rightImage, 4525095):removeAllChildren()
    UI_GetUIImageView(rightImage, 4525092):addChild(Active,1,1)
    UI_GetUIImageView(rightImage, 4525095):addChild(Stage,1,1)

    Active:setTouchEnabled(true)
    Stage:setTouchEnabled(true)

    Active:setTag(detail.iActiveSkillID)
    Stage:setTag(detail.iStageSkillID)
    
    Active:addTouchEventListener(Skillinfo)
    Stage:addTouchEventListener(Skillinfo)
    --�������
    local step = GodAnimalSystem_getStep(detail.iLevelStep)
    local stepNum = GodAnimalSystem_getStepNum(detail.iLevelStep)


    --����
    UI_GetUILabel(rightImage, 4525138):setText(animalLocal.m_name)
    --��
    local stepLabel = UI_GetUILabel(rightImage, 4525198)
    stepLabel:setVisible( stepNum > 0 )
    stepLabel:setText("+"..stepNum)
    stepLabel:setColor(UI_GetColor(step+1))
    --�׵�ͼƬ
     UI_GetUIImageView(rightImage, 4525088):loadTexture(GodAnimalSystem_getPath("Step",step))
end
--��ȡ·��
function GodAnimalSystem_getPath(kind,id)
    if( kind =="Step"  )then
        return "Common/Fort_Rank_0"..id..".png"
    elseif kind == "iconHero" then
        return "Icon/HeroIcon/"..id..".png"
    elseif kind == "skill" then
        return "Icon/Skill/"..id..".png"
    elseif kind == "skillCommon" then
        return "Common/Icon_Bg_0"..(id+21)..".png"
    elseif kind == "animalHeadCommon" then
        return "Common/Icon_Bg_00"..(id+1)..".png"
    elseif kind == "heroType" then
        return "Common/Icon_001_0"..(id)..".png"
    end

end
--���������ʱ����ʾ��ϸ��Ϣ�����ṩ����
function GodAnimalSystem_ShowData(widget,detail)
    widgetLeft = UI_GetUIImageView(widget, 4524935)
    --�����ٻ�����---------------------------------------------------------
    local callLayout = UI_GetUIButton(widgetLeft, 4525207)
    callLayout:setVisible(false)
    callLayout:setTouchEnabled(false)
    UI_GetUIButton(callLayout, 4535116):setTouchEnabled(false)
    -----------------------------------------------------------------------
    --��ť�ص�--------------------------------------
    --��ս
    local function fight(sender,eventType)
        if( eventType == TOUCH_EVENT_ENDED ) then
            GodAnimalSystem_GetAnimalActive(detail.dwObjectID)
        end      
    end
    
     --����
    local function inheritance(sender,eventType)
        if( eventType == TOUCH_EVENT_ENDED ) then
            GodAnimalSystem_ShowInheritance(widget)
            GodAnimalSystem_Inherit(widget, detail)
            GodAnimalSystem_SetSelected(4525100)
        end
    end
     --����
    local function train(sender,eventType)
        if( eventType == TOUCH_EVENT_ENDED ) then
            GodAnimalSystem_ShowTrain(widget)
            GodAnimalSystem_GetAnimalData(detail.dwObjectID)
			if (g_isGuide) then
				Guide_GoNext();
			end
            GodAnimalSystem_SetSelected(4525111)
        end
    end
    ------------------------------------------------
    --����
    local showData = UI_GetUIImageView(widgetLeft, 4525191)
    
    showData:setVisible(true)
    UI_GetUIButton(showData, 4525109):setTouchEnabled(true)
    UI_GetUIButton(showData, 4525110):setTouchEnabled(true) 
    UI_GetUIButton(showData, 4525100):setTouchEnabled(true)   
    UI_GetUIButton(showData, 4525111):setTouchEnabled(true)
    UI_GetUIButton(showData, 4525098):setTouchEnabled(true)
    --��ս
    UI_GetUIButton(showData, 4525109):addTouchEventListener(fight)
    --����
    UI_GetUIButton(showData, 4525100):addTouchEventListener(inheritance)
    --����
    UI_GetUIButton(showData, 4525111):addTouchEventListener(train)
    --�ȼ�
    UI_GetUILabel(showData, 4525140):setText(detail.iLevel)
    --ս����
    UI_GetUILabel(showData, 4525181):setText(detail.iFightValue)
    --����
    UI_GetUILabel(showData, 4525182):setText(detail.szPropList[1].iValue)
    --�ȼ�
    UI_GetUILabel(showData, 4525183):setText(detail.szPropList[2].iValue)
end
--����������Ҫ���ⷢ����Ϣ��������׵����ݳ�ʼ������GodAnimalSystem_ShowData�ֿ�
function GodAnimalSystem_SetStepLevelUpInfo(info)
    local widget = UI_GetBaseWidgetByName("GodAnimalSystem")
    widgetLeft = UI_GetUIImageView(widget, 4524935)
    local showData = UI_GetUIImageView(widgetLeft, 4525191)

    
    --ӵ�л�����
    local haveNum = -1
    if info.bTouchMaxLv ~= true then
        haveNum = GetLocalPlayer():GetPlayerBag():GetItemCountByItemId(info.szConsumeItem[1].iItemID)
    end
    --����
    local function StepLevelUp()
        --if( eventType == Touch_EVENT_BEGAN ) then
            GodAnimalSystem_GetAnimalStepLevelUp(info.dwObjectID)
        --end
        --print("----")
    end
    --������ʾ��
    local function stepLevelUp(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            if info.bTouchMaxLv then
                StepLevelUp()
            elseif(haveNum>=info.szConsumeItem[1].iNeedCount) then
                local tab = {}
                tab.info = FormatString("StepUpExpense1")..info.iLevelStepSilverCost..FormatString("StepUpExpense2")
                tab.msgType = EMessageType_LeftRight
                tab.leftFun = StepLevelUp
                Messagebox_Create(tab)
            else
                createPromptBoxlayout(FormatString("NotEnoughSoulStepUp"))

            end
        end
    end
    --����
    UI_GetUIButton(showData, 4525110):addTouchEventListener(stepLevelUp)
    --�޸��������� 
    if info.bTouchMaxLv then
        UI_GetUILabel(showData, 4525144):setText(FormatString("NewHeroSystem_HeroMaxAscending"))
        UI_GetUILoadingBar(showData, 4525173):setPercent(100)
        --���λ�ȡ��ʽ
        UI_GetUIButton(showData, 4525098):setTouchEnabled(false)
        UI_GetUIButton(showData, 4525098):setVisible(false)
    else
        --���ý�����-��ֵ
        UI_GetUILabel(showData, 4525144):setText(haveNum.."/"..info.szConsumeItem[1].iNeedCount)
        percent = haveNum*100/info.szConsumeItem[1].iNeedCount
        local temp = percent>100 and 100
        percent = temp or percent
        --���ý�����-������
        UI_GetUILoadingBar(showData, 4525173):setPercent(percent)
        --�����Ƭ����
        local function GetFragment(sender,eventType)
            if( eventType == TOUCH_EVENT_ENDED ) then
                GodAnimalSystem_GetFragment(info.szConsumeItem[1].iItemID,info.szConsumeItem[1].iNeedCount)
            end
        end
        --"+"��ȡ����
        UI_GetUIButton(showData, 4525098):setTouchEnabled(true)
        UI_GetUIButton(showData, 4525098):setVisible(true)
        UI_GetUIButton(showData, 4525098):addTouchEventListener(GetFragment)
    end
end
--�����ﲻ����ʱ����ʾ�ٻ�����
function GodAnimalSystem_ShowDataNG(widget,detail)
    widgetRight = UI_GetUIImageView(widget, 4524935)
    --������ʾ��ϸ��Ϣ����İ�ť------------------------
    local showData = UI_GetUIImageView(widgetRight, 4525191)

    showData:setVisible(false)
    UI_GetUIButton(showData, 4525109):setTouchEnabled(false)
    UI_GetUIButton(showData, 4525110):setTouchEnabled(false) 
    UI_GetUIButton(showData, 4525100):setTouchEnabled(false)   
    UI_GetUIButton(showData, 4525111):setTouchEnabled(false)
    UI_GetUIButton(showData, 4525098):setTouchEnabled(false)
    -------------------------------------------------
    --�����ٻ�����------------------------------------
    local callLayout = UI_GetUIButton(widgetRight, 4525207)
    callLayout:setVisible(true)
    callLayout:setTouchEnabled(true)
    UI_GetUIButton(callLayout, 4535116):setTouchEnabled(true)
    -------------------------------------------------
    local NGGodAnimalData = GetGameData(DataFileGodAniaml,detail.iBaseID,"stGodAnimalData")
    local haveNum = GetLocalPlayer():GetPlayerBag():GetItemCountByItemId(NGGodAnimalData.m_changeItemId)
    local allNum = NGGodAnimalData.m_changeNumber
    local itemData = GetGameData(DataFileItem,NGGodAnimalData.m_changeItemId,"stItemData")
    --��ȷ���ٻ�����ť��Ӧ
    local function callAnimalDetermine(sender,eventType)
        if eventType == Touch_EVENT_BEGAN then
            GodAnimalSystem_CallAnimal(detail.iBaseID)
        end
    end
    --"�ٻ�"��ť��Ӧ
    local function callAnimal(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            if haveNum>= allNum then
                local tab = {}
                tab.info = FormatString("CallExpense1")..NGGodAnimalData.m_cost..FormatString("CallExpense2")--���޸�
                tab.msgType = EMessageType_LeftRight
                tab.leftFun = callAnimalDetermine
                Messagebox_Create(tab)
            else
                createPromptBoxlayout(FormatString("NotEnoughSoul"))
            end
        end
    end
    --���ͼ��
    UI_GetUIImageView(callLayout, 4525828):removeAllChildren()
    UI_GetUIImageView(callLayout, 4525828):addChild(UI_ItemIconFrame(UI_GetItemIcon(NGGodAnimalData.m_changeItemId, -1),itemData.m_quality) )
    UI_GetUILabel(callLayout, 4525224):setText(NGGodAnimalData.m_name)
    UI_GetUILabel(callLayout, 4525226):setText(haveNum.."/"..allNum)

    callLayout:addTouchEventListener(callAnimal)
    
    --�����Ƭ����
    local function GetFragment(sender,eventType)
        if( eventType == TOUCH_EVENT_ENDED ) then
            GodAnimalSystem_GetFragment(NGGodAnimalData.m_changeItemId,allNum)
         end
    end
    UI_GetUIButton(callLayout, 4535116):addTouchEventListener(GetFragment)
end
------------------------------------------------------------------------------------
--����
function GodAnimalSystem_Inherit(widget, detail)
    local leftImage = UI_GetUIImageView(widget, 4524938)
    local inheritance = UI_GetUIImageView(leftImage, 4525237)   
 
    --ɢ��Ӣ��ID
    local passerDwObjectID=-1
    --��ʼ��Ԥ����Ϣ
    local StepLevelUpInfo = UI_GetUIImageView(inheritance, 4525255)
    StepLevelUpInfo:setVisible(false)
    ----�ȼ�
    --UI_GetUILabel(inheritance, 4525312):setText(999)
    ----����
    --UI_GetUILabel(inheritance, 4525347):setText(999999)
    ----����
    --UI_GetUILabel(inheritance, 4525348):setText(999999) 
    --��ɢ������ͼ������
    UI_GetUIImageView(inheritance, 4526264):setVisible(false)
    --ͭ������
    UI_GetUILabel(inheritance, 4525354):setText(0)
    --���з��ġ�ս��
    UI_GetUIImageView(inheritance, 4525270):setVisible(false)
    --����ɢ��Ӣ��--------------------------------------------------------
    local function GodAnimalSystem_SetInheritHero(id)
        local widget = UI_GetBaseWidgetByName("GodAnimalSystem");
        local leftImage = UI_GetUIImageView(widget, 4524938)
        local inheritance = UI_GetUIImageView(leftImage, 4525237)
        local GodAnimal = GetLocalPlayer():GetGodAnimalList()[id]
        --������......
        local step =  GodAnimal:GetInt(EGodAnimal_LevelStep)
        local step_ = (step - step%10)/10+1
        --�^��
        UI_GetUIImageView(inheritance, 4526264):setVisible(true)
        UI_GetUIImageView(inheritance, 4526264):loadTexture(GodAnimalSystem_getPath("iconHero", GodAnimal:getGodAnimalData().m_ID))
        --ͷ�����
        UI_GetUIImageView(inheritance, 4526268):loadTexture(GodAnimalSystem_getPath("animalHeadCommon", step_))
        --����ɢ��ID
        passerDwObjectID=GodAnimal:GetInt(EGodAnimal_ObjId)

        --�Ƿ��ս
        if( GetLocalPlayer():GetGodAnimalByDwObject(passerDwObjectID):GetBool(EGodAnimal_IsActive) ) then 
            UI_GetUIImageView(inheritance, 4525270):setVisible(true)
        else
            UI_GetUIImageView(inheritance, 4525270):setVisible(false)
        end    
        
        GodAnimalSystem_inheritanceData(detail.dwObjectID,passerDwObjectID)  
    end
    -------------------------------------------------------------------
    ----ɢ��Ӣ���б�---------------------------------------------------------
    local function GodAnimalSystem_InheritHero(detail)
        local widget = UI_CreateBaseWidgetByFileName("UIExport/DemoLogin/inheritanceHero.json")
        local listView = UI_GetUIListView(widget, 4526304)       
        --�˳�
        UI_GetUIButton(widget, 4526306):addTouchEventListener(UI_ClickCloseCurBaseWidget)
        --��ӿ�����ɢ���ĳ���
        local GodAnimalList = GetLocalPlayer():GetGodAnimalList()

        --ѡ��ɢ��Ӣ��
        local function choosInheritHero(sender,eventType)
            if eventType == TOUCH_EVENT_ENDED then
                local id = tolua.cast(sender,"ImageView"):getTag()-1400
                GodAnimalSystem_SetInheritHero(id)
                UI_ClickCloseCurBaseWidget(sender,TOUCH_EVENT_ENDED)
            end
        end
        --����
        local function inheritance(sender,eventType)
            if eventType == TOUCH_EVENT_ENDED then
                local id = tolua.cast(sender,"ImageView"):getTag()-1400
                GodAnimalSystem_SetInheritHero(id)
                UI_ClickCloseCurBaseWidget(sender,TOUCH_EVENT_ENDED)
            end
        end
        for i=0,GodAnimalList:size()-1,1 do
            local GodAnimalData = GodAnimalList[i]:getGodAnimalData()
            --�ȼ�Ҫ�����Լ�
            if GodAnimalList[i]:GetInt(EGodAnimal_Level) > detail.iLevel then
                local GAwidget = UI_GetUIImageView(widget, 4526318):clone()
                listView:pushBackCustomItem(GAwidget)

                --name
                local name = GodAnimalData.m_name
        
                local step = GodAnimalList[i]:GetInt(EGodAnimal_LevelStep)
                if step%10 >0 then
                    name = name.."+"..step%10
                end
                UI_GetUILabel(GAwidget, 4526327):setText(name)
                --level
                UI_GetUILabel(GAwidget, 4526322):setText(GodAnimalList[i]:GetInt(EGodAnimal_Level))
                --������......
                local step_ = (step - step%10)/10+1
                UI_GetUIImageView(GAwidget, 4526326):loadTexture(GodAnimalSystem_getPath("Step",step_))
                --�^��
                UI_GetUIImageView(GAwidget, 4526325):loadTexture(GodAnimalSystem_getPath("iconHero", GodAnimalData.m_ID))
                --ͷ�����
                UI_GetUIImageView(GAwidget, 4526324):loadTexture(GodAnimalSystem_getPath("animalHeadCommon", step_))
                --�Ƿ��ս
                if( GodAnimalList[i]:GetBool(EGodAnimal_IsActive) ) then 
                    UI_GetUIImageView(GAwidget, 4526319):setVisible(true)
                else
                    UI_GetUIImageView(GAwidget, 4526319):setVisible(false)
                end  
                --������ʾ���ɳ�
                GAwidget:addTouchEventListener(choosInheritHero)
                GAwidget:setTag(i+1400)
            end
        end
        UI_GetUIImageView(widget, 4526318):setVisible(true)
    end
    ------------------------------------------------------------------------
    --����
    local function cancel(sender,eventType )
        if eventType == TOUCH_EVENT_ENDED then
            GodAnimalSystem_ShowListView(widget)
            GodAnimalSystem_refreshListView(widget)
            GodAnimalSystem_SetSelected(-1)
        end
    end
    --����
    local function determine(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            if passerDwObjectID == -1 then
                    createPromptBoxlayout(FormatString("NoInheritHero"))
                return
            end 
        end
    end
    --ѡ��ɢ������
    local function choose(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then  
            GodAnimalSystem_InheritHero(detail)
        end
    end
    --����
    UI_GetUIButton(inheritance, 4525372):addTouchEventListener(determine)
    --����
    UI_GetUIButton(inheritance, 4525374):addTouchEventListener(cancel)
    --�ȼ�
    UI_GetUILabel(inheritance, 4525307):setText(detail.iLevel)
    --����
    UI_GetUILabel(inheritance, 4525309):setText(detail.szPropList[1].iValue)
    --����
    UI_GetUILabel(inheritance, 4525311):setText(detail.szPropList[2].iValue)
    UI_GetHeroIcon(detail.iBaseID, count, heroType)
    --�̳г���
    UI_GetUIImageView(inheritance, 4525240):loadTexture(GodAnimalSystem_getPath("iconHero",detail.iBaseID))
    --�߿�
    local step_ = (detail.iLevelStep - detail.iLevelStep%10)/10+1
    UI_GetUIImageView(inheritance, 4526265):loadTexture(GodAnimalSystem_getPath("animalHeadCommon",step_))
    --����ɢ��Ӣ��
    UI_GetUIImageView(inheritance, 4526264):loadTexture("UIExport/DemoLogin/Common/Icon_Bg_base.png")
    --����ɢ��Ӣ�۱߿�
    UI_GetUIImageView(inheritance, 4526268):loadTexture(GodAnimalSystem_getPath("animalHeadCommon",1))
    --�Ƿ��ս
    if( GetLocalPlayer():GetGodAnimalByDwObject(detail.dwObjectID):GetBool(EGodAnimal_IsActive) ) then 
        UI_GetUIImageView(inheritance, 4525272):setVisible(true)
    else
        UI_GetUIImageView(inheritance, 4525272):setVisible(false)
    end
    --ѡ��ɢ������
    inheritance:addTouchEventListener(choose)
end
--��ʾ���е�Ԥ����Ϣ
function GodAnimalSystem_InheritPrediction(widget,info)
    local detail = info.acceptPostDetail
    local leftImage = UI_GetUIImageView(widget, 4524938)
    local inheritance = UI_GetUIImageView(leftImage, 4525237) 
    local StepLevelUpInfo = UI_GetUIImageView(inheritance, 4525255)
    StepLevelUpInfo:setVisible(true) 
    --�ȼ�
    UI_GetUILabel(StepLevelUpInfo, 4525312):setText(detail.iLevel)
    --����
    UI_GetUILabel(StepLevelUpInfo, 4525347):setText(detail.szPropList[1].iValue)
    --����
    UI_GetUILabel(StepLevelUpInfo, 4525348):setText(detail.szPropList[2].iValue)
    --ͭ������
    UI_GetUILabel(inheritance, 4525354):setText(info.iInheritSilverCost)
     --����
    local function Inheritance()     
        GodAnimalSystem_inheritance(detail.dwObjectID,info.passerDetail.dwObjectID)
        GodAnimalSystem_GetAnimalData(detail.dwObjectID)  
    end
    --������ʾ��
    local function determine(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            local tab = {}
            tab.info = FormatString("InheritanceExpense1")..info.iInheritSilverCost..FormatString("InheritanceExpense2")
            tab.msgType = EMessageType_LeftRight
            tab.leftFun = Inheritance
            Messagebox_Create(tab)
        end
    end
    --����
    UI_GetUIButton(inheritance, 4525372):addTouchEventListener(determine)
end
------------------------------------------------------------------------------------------
--����
function GodAnimalSystem_Train(widget, detail)
    local leftImage = UI_GetUIImageView(widget, 4524938)
    --local inheritance = UI_GetUIImageView(leftImage, 4525237)   
    local train = UI_GetUIImageView(leftImage, 4526346)
    --����
     local function cancel(sender,eventType )
        if eventType == TOUCH_EVENT_ENDED then
            GodAnimalSystem_ShowListView(widget)
            GodAnimalSystem_refreshListView(widget)
            GodAnimalSystem_SetSelected(-1)
        end
    end
    --����
    local function Train(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
			if (g_isGuide) then
				Guide_GoNext();
			end
            GodAnimalSystem_TrainMsg(detail.dwObjectID)
        end
    end
    --����
    UI_GetUIButton(train, 4526357):addTouchEventListener(cancel)
    --����
    UI_GetUIButton(train, 4526354):addTouchEventListener(Train)
    --������
    UI_GetUILoadingBar(train, 4526351):setPercent(detail.iCurExp/detail.iNeedExp*100)
end
--������Ϣ��ʾ
function GodAnimalSystem_StepLevelUp(info)
    local widget = UI_CreateBaseWidgetByFileName("UIExport/DemoLogin/GodAnimalStepLevelUP.json")
    --UI_GetUIButton(widget, 4526751):addTouchEventListener(UI_ClickCloseCurBaseWidget)
    local GodAnimalData = GetLocalPlayer():GetGodAnimalByDwObject(info.dwNewGodAnimalObjectId):getGodAnimalData()
    -----------------------ԭ��---------------------------------------------
    --ԭ�У�ͷ��
    UI_GetUIImageView(widget, 4526765):loadTexture(GodAnimalSystem_getPath("iconHero", GodAnimalData.m_ID))
    local step_ = GodAnimalSystem_getStep(info.oldState.iGodAnimalLevelStep)
    --ԭ�У��ɡ���
    UI_GetUIImageView(widget, 4526774):loadTexture(GodAnimalSystem_getPath("Step",step_))
    --ԭ�У�ͷ�����
    UI_GetUIImageView(widget, 4526766):loadTexture(GodAnimalSystem_getPath("animalHeadCommon", step_))
    --����
    local name = GodAnimalData.m_name
    if GodAnimalSystem_getStepNum(info.oldState.iGodAnimalLevelStep)>0 then
        name = name.."+"..GodAnimalSystem_getStepNum(info.oldState.iGodAnimalLevelStep)
    end
    UI_GetUILabel(widget, 4526781):setText(name)
    --------------------------------------------------------------------------
    ------------------------��ǰ----------------------------------------------
    --���ڣ�ͷ��
    UI_GetUIImageView(widget, 4526771):loadTexture(GodAnimalSystem_getPath("iconHero", GodAnimalData.m_ID))
    local step_ = GodAnimalSystem_getStep(info.newState.iGodAnimalLevelStep)
    --���ڣ��ɡ���
    UI_GetUIImageView(widget, 4526777):loadTexture(GodAnimalSystem_getPath("Step",step_))
    --���ڣ�ͷ�����
    UI_GetUIImageView(widget, 4526772):loadTexture(GodAnimalSystem_getPath("animalHeadCommon", step_))
    --����
    local name = GodAnimalData.m_name
    if (GodAnimalSystem_getStepNum(info.newState.iGodAnimalLevelStep)>0) then
        name = name.."+"..GodAnimalSystem_getStepNum(info.newState.iGodAnimalLevelStep)
    end
    UI_GetUILabel(widget, 4526788):setText(name)
    --------------------------------------------------------------------------
    --����
    UI_GetUILabel(widget, 4526804):setText(info.oldState.iHpGrow/10000)
    UI_GetUILabel(widget, 4526810):setText((info.newState.iHpGrow-info.oldState.iHpGrow)/10000)
    UI_GetUILabel(widget, 4526816):setText("("..FormatString("en_LifeAtt_MaxHP").."+"..info.iHPAddValue..")")
    --����
    UI_GetUILabel(widget, 4526800):setText(info.oldState.iAttGrow/10000)
    UI_GetUILabel(widget, 4526812):setText((info.newState.iAttGrow-info.oldState.iAttGrow)/10000)
    UI_GetUILabel(widget, 4526813):setText("("..FormatString("en_LifeAtt_Att").."+"..info.iAttAddValue..")")

end
--�����Ƭ����
function GodAnimalSystem_GetFragment(iItemID,need)
    local widget = UI_CreateBaseWidgetByFileName("UIExport/DemoLogin/GodAnimalFragment.json")
    UI_GetUIButton(widget, 4528164):addTouchEventListener(UI_ClickCloseCurBaseWidget)
   print("iItemID=="..iItemID)
    --��ȡ�������Ƭ�Ļ�����Ϣ
    local itemData = GetGameData(DataFileItem,iItemID,"stItemData")
    --ͼ��
    local icon = UI_ItemIconFrame(UI_GetItemIcon(iItemID, -1), itemData.m_quality)
    UI_GetUIImageView(widget, 4528132):addChild(icon)
    --����
    UI_GetUILabel(widget, 4528135):setText(itemData.m_name)
    --ӵ�л�����
    local haveNum = GetLocalPlayer():GetPlayerBag():GetItemCountByItemId(iItemID)
    --��ʾ����������
    UI_GetUILabel(widget, 4528137):setText( "("..haveNum.."/"..need..")" )
    --����þ�
    local function GetMethodsOne(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            Packet_Cmd(GameServer_pb.CMD_DREAMLAND_OPEN_REQSECTON);
			ShowWaiting()
        end
    end
    --�̳�
    local function GetMethodsTwo(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            UI_CloseCurBaseWidget()
            Shop_Create()
        end
    end
    --����þ�
    UI_GetUIButton(widget, 4528153):addTouchEventListener(GetMethodsOne)
    --�̳�
    UI_GetUIButton(widget, 4528150):addTouchEventListener(GetMethodsTwo)
end
----------------------------------------------------------------------------------------
--�����������沢���γ����б�ʹ��н���
function GodAnimalSystem_ShowTrain(widget)
    local leftImage = UI_GetUIImageView(widget, 4524938)
    local inheritance = UI_GetUIImageView(leftImage, 4525237)   
    local train = UI_GetUIImageView(leftImage, 4526346)
    local listView = UI_GetUIListView( leftImage , 4525076)
    listView:removeAllItems()
    --�ָ����ɳ衱�б�İ�����Ӧ
    listView:setVisible(false)
    listView:setTouchEnabled(false)
    --����"����"����ġ����С��͡�ȡ������ť  
    --ȷ��
    UI_GetUIButton(inheritance, 4525372):setTouchEnabled(false)
    --ȡ��
    UI_GetUIButton(inheritance, 4525374):setTouchEnabled(false)
    --ɢ������
    inheritance:setTouchEnabled(false)
    inheritance:setVisible(false)  
    --���Ρ�����������
    train:setVisible(true)
    UI_GetUIButton(train, 4526354):setTouchEnabled(true)
    UI_GetUIButton(train, 4526357):setTouchEnabled(true)
end
--����н��沢���γ����б����������
function GodAnimalSystem_ShowInheritance(widget)

    local leftImage = UI_GetUIImageView(widget, 4524938)
    local inheritance = UI_GetUIImageView(leftImage, 4525237)   
    local train = UI_GetUIImageView(leftImage, 4526346)
    local listView = UI_GetUIListView( leftImage , 4525076)
    --�ָ����ɳ衱�б�İ�����Ӧ
    listView:setVisible(false)
    listView:setTouchEnabled(false)
    --����"����"����ġ����С��͡�ȡ������ť  
    --ȷ��
    UI_GetUIButton(inheritance, 4525372):setTouchEnabled(true)
    --ȡ��
    UI_GetUIButton(inheritance, 4525374):setTouchEnabled(true)
    --ɢ������
    inheritance:setTouchEnabled(true)
    inheritance:setVisible(true)  
    --���Ρ�����������
    train:setVisible(false)
    UI_GetUIButton(train, 4526354):setTouchEnabled(false)
    UI_GetUIButton(train, 4526357):setTouchEnabled(false)
    --��ɢ������ͼ������
    UI_GetUIImageView(inheritance, 4526264):setVisible(false)
    listView:removeAllItems()
    print("-----------------------------GodAnimalSystem_ShowInheritance-------------------------")
end
--�����ɳ��б����δ��н������������
function GodAnimalSystem_ShowListView(widget)

    local leftImage = UI_GetUIImageView(widget, 4524938)
    local inheritance = UI_GetUIImageView(leftImage, 4525237)
    local train = UI_GetUIImageView(leftImage, 4526346)
    local listView = UI_GetUIListView( leftImage , 4525076)
    listView:removeAllItems()
    listView:setVisible(true)
    --�ָ����ɳ衱�б�İ�����Ӧ
    listView:setTouchEnabled(true)
    --���Ρ�����������
    train:setVisible(false)
    UI_GetUIButton(train, 4526354):setTouchEnabled(false)
    UI_GetUIButton(train, 4526357):setTouchEnabled(false)
    --����"����"����ġ����С��͡�ȡ������ť  
    --ȷ��
    UI_GetUIButton(inheritance, 4525372):setTouchEnabled(false)
    --ȡ��
    UI_GetUIButton(inheritance, 4525374):setTouchEnabled(false)
    --ɢ������
    inheritance:setTouchEnabled(false)
    inheritance:setVisible(false)
end
--------------------------------------------------------------------------------------------------------------------------
--������Ϣ;��ȡ������ϸ��Ϣ
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_GODANIMAL_DETAIL, "GodAnimalSystem_ShowGodAnimalDetai" )
--������Ϣ;��ȡδ��õ�������ϸ��Ϣ
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_GODANIMAL_DETAIL_BYID, "GodAnimalSystem_ShowNotHaveGodAnimalDetai" )
--������Ϣ;�ٻ��ɹ�
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_GODANIMAL_ANIMALSOUL_ACTIVE, "GodAnimalSystem_ActionactivitySuccess" )
--������Ϣ������
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_GODANIMAL_EXEINHERIT, "GodAnimalSystem_ExeGodAnimalInheritReturn" )
--������Ϣ����ѯ���к������
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_GODANIMAL_QUERYINHERIT, "GodAnimalSystem_InheritanceInfo" )
--������Ϣ������
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_GODANIMAL_TRAIN, "GodAnimalSystem_TrainSuccess" )
--������Ϣ�����ײ�ѯ
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_GODANIMAL_QUERYLEVELSTEP, "GodAnimalSystem_QueryStepLevelUpInfo" )
--������Ϣ������
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_GODANIMAL_EXELEVELSTEPUP, "GodAnimalSystem_QueryStepLevelUp" )
--������Ϣ����ս
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_GODANIMAL_ACTIVE, "GodAnimalSystem_GetGodAnimalPlayed" )
---------------------------------------------------------------------------------------------------------------------------
--��ȡ������ϸ��Ϣ
function GodAnimalSystem_ShowGodAnimalDetai(pkg)
    EndWaiting()

    local info = GameServer_pb.Cmd_Sc_QueryGodAnimalDetai()
    info:ParseFromString(pkg)
    Log("info===="..tostring(info))
    local widget = UI_GetBaseWidgetByName("GodAnimalSystem")

    if widget == nil then
        widget = GodAniamalSystem_createWidget()

    end

    --�ұ������е��Ϸ���������
    GodAnimalSystem_setPublicData(widget,info.detail)
    --���������ʱ����ʾ��ϸ��Ϣ�����ṩ����
    GodAnimalSystem_ShowData(widget,info.detail)
    --ˢ�¾�����ʾ
    GodAnimalSystem_Train(widget, info.detail)
    --���´��н���
    GodAnimalSystem_Inherit(widget,info.detail)
    --ˢ�³����б�
   if g_isRefreshListView then
        GodAnimalSystem_refreshListView(widget)
        g_isRefreshListView = false
    end
   
   g_GodAnimalSystem_lastlevel = info.detail.iLevel
end
--��ȡδ��õ�������ϸ��Ϣ
function GodAnimalSystem_ShowNotHaveGodAnimalDetai(pkg)
   EndWaiting()
   local info = GameServer_pb.CMD_GODANIMAL_DETAIL_BYID_SC()
   info:ParseFromString(pkg)
   Log("Heroxxxxxx==="..tostring(info))
   local widget = UI_GetBaseWidgetByName("GodAnimalSystem")
   --�ұ������е��Ϸ���������
   GodAnimalSystem_setPublicData(widget,info.detail)
   --�ٻ�����
   GodAnimalSystem_ShowDataNG(widget,info.detail)
end 
--�ٻ��ɹ�
function GodAnimalSystem_ActionactivitySuccess(pkg)
   EndWaiting()
   local widget = UI_GetBaseWidgetByName("GodAnimalSystem")
   --���³����б�
   local animalIDList = vector_int_:new_local() 
   GetLocalPlayer():sortGodAnimalWithId(animalIDList)

   GodAnimalSystem_refreshListView(widget,animalIDList)

   for i=0,animalIDList:size()-1,1 do
        local animal = GetLocalPlayer():GetGodAnimalByAnimalId(animalIDList[i])
        if animal:getGodAnimalData().m_ID ==g_GodAnimalSystem_callID then
            print("i==============="..i)
            GodAnimalSystem_refreshListViewHL(i,animalIDList:size(),widget)
            --��ʾ�ٻ��ɳ������
            local ID = animal:GetInt(EGodAnimal_ObjId)
            GodAnimalSystem_GetAnimalStepLevelUpInfo(ID)
            GodAnimalSystem_GetAnimalData(ID)

                        --�����һ���ɳ������
            --GodAnimalSystem_GetAnimalData(animalList[i]:GetInt(EGodAnimal_ObjId))
            --��һ���ɳ����������Ԥ��
            --GodAnimalSystem_GetAnimalStepLevelUpInfo(animalList[i]:GetInt(EGodAnimal_ObjId))
            return
        end
    end
end 
--����
function GodAnimalSystem_ExeGodAnimalInheritReturn(pkg)
   EndWaiting()
end
--��ѯ���к������
function GodAnimalSystem_InheritanceInfo(pkg)
   EndWaiting()
   local widget = UI_GetBaseWidgetByName("GodAnimalSystem")
   local info = GameServer_pb.Cmd_Sc_QueryGodAnimalInherit()
   info:ParseFromString(pkg)
   Log("______info ====="..tostring(info)) 
   --��ʾ���е�Ԥ����Ϣ
   GodAnimalSystem_InheritPrediction(widget,info)
   
end
--����
function GodAnimalSystem_TrainSuccess(pkg)
    EndWaiting()
    local info = GameServer_pb.Cmd_Sc_GoldAnimalTrain()
    info:ParseFromString(pkg)
    local widget = UI_GetBaseWidgetByName("GodAnimalSystem")
    if widget then 
        Log("train info==========="..tostring(info))

        local leftImage = UI_GetUIImageView(widget, 4524938)  
        local train = UI_GetUIImageView(leftImage, 4526346)

        
        local uplevel = info.detail.iLevel - g_GodAnimalSystem_lastlevel
        --����-����������
        GodAnimalSystem_UpdateLoadingbar(train,info.detail,uplevel)
        --����-�ȼ��;���
        GodAnimalSystem_UpdateNumberAction(train,info,uplevel)
        if uplevel>0 then        
            --���³�������
            GodAnimalSystem_ShowData(widget,info.detail)
        end
        g_GodAnimalSystem_lastlevel = info.detail.iLevel
    end 
end 
--���ײ�ѯ
function GodAnimalSystem_QueryStepLevelUpInfo(pkg) 
    EndWaiting()
    local info = GameServer_pb.Cmd_Sc_QueryGodAnimalLevelStep()
    info:ParseFromString(pkg)  
    print("____stepLevel===="..tostring(info))
    
    GodAnimalSystem_SetStepLevelUpInfo(info) 
end 
function GodAnimalSystem_QueryStepLevelUp(pkg)
    EndWaiting()

    local info = GameServer_pb.CMD_GODANIMAL_EXELEVELSTEPUP_SC()
    info:ParseFromString(pkg)  
    print("+++++++stepLevel===="..tostring(info)) 

    --���³����б�
    local widget = UI_GetBaseWidgetByName("GodAnimalSystem")  
    GodAnimalSystem_refreshListView(widget) 
    --��ѯ��ǰ����  
    g_isRefreshListView = true
    GodAnimalSystem_GetAnimalData(info.dwNewGodAnimalObjectId)
    
    GodAnimalSystem_StepLevelUp(info)
end
--��ս
function GodAnimalSystem_GetGodAnimalPlayed(pkg)
    EndWaiting()
    local info = GameServer_pb.Cmd_Sc_GoldAnimalActive()
    info:ParseFromString(pkg)
    local widget = UI_GetBaseWidgetByName("GodAnimalSystem")
    print("GodAnimalSystem_GetGodAnimalPlayed = "..tostring(info))
    --���ó�ս
    GetLocalPlayer():SetGodAnimalActive(info.dwObjectID)
    --���³����б�
    GodAnimalSystem_refreshListView(widget)
    GodAnimalSystem_refreshListViewHL(0,1,widget)
end 
---------------------------------������Ϣ����������ض�����------------------------------------
--����-����������
function GodAnimalSystem_UpdateLoadingbar(widget,detail,uplevel) 
    local upExppercent = detail.iCurExp / detail.iNeedExp
    UI_GetUILoadingBar(widget, 4526351):setPercentSlowly(upExppercent * 100 + uplevel * 100,1.0)
end
--����-�ȼ��;���
function GodAnimalSystem_UpdateNumberAction(widget,info,uplevel)
   --���� action
	local animaltionlayoutPositionX , animaltionlayoutPositionY = widget:getPosition()

	local bezierconfig = ccBezierConfig:new_local()
	bezierconfig.controlPoint_1 = ccp(animaltionlayoutPositionX,animaltionlayoutPositionY + 120)
	bezierconfig.controlPoint_2 = ccp(animaltionlayoutPositionX - 100,animaltionlayoutPositionY + 120)
	bezierconfig.endPosition = ccp(animaltionlayoutPositionX - 120,animaltionlayoutPositionY + 50 )
	local bezierAction = CCBezierTo:create(1.0,bezierconfig)

	local fadeOut = CCFadeOut:create(0.5)
	local actionArray = CCArray:create()
	local  function rmoveSelf(sender)
	    local sender = tolua.cast(sender,"Label")
		sender:removeFromParent()
	end
	local callback = CCCallFuncN:create(rmoveSelf)
	actionArray:addObject(bezierAction)
	actionArray:addObject(fadeOut)
	actionArray:addObject(callback)
	local  action = CCSequence:create(actionArray)

	if uplevel ~= 0 then
        local levelUPLabel = CompLabel:GetDefaultCompLabel(FormatString("GadAnimal_LevelUP",uplevel),192)
		levelUPLabel:setPosition( ccp(animaltionlayoutPositionX,animaltionlayoutPositionY))
		levelUPLabel:setAnchorPoint(ccp(0.5,0.5))
		widget:addChild(levelUPLabel,1000,1000)
		levelUPLabel:runAction(action)
	end

	----����action
    local bezierconfig = ccBezierConfig:new_local()
	bezierconfig.controlPoint_1 = ccp(animaltionlayoutPositionX,animaltionlayoutPositionY + 120)
	bezierconfig.controlPoint_2 = ccp(animaltionlayoutPositionX + 100,animaltionlayoutPositionY + 120)
	bezierconfig.endPosition = ccp(animaltionlayoutPositionX + 120,animaltionlayoutPositionY + 50 )
	local bezierAction = CCBezierTo:create(1.0,bezierconfig)

	local fadeOut = CCFadeOut:create(0.5)
	local actionArray = CCArray:create()
	local  function rmoveSelf(sender)
	    local sender = tolua.cast(sender,"Label")
		sender:removeFromParent()
	end
	local callback = CCCallFuncN:create(rmoveSelf)
	actionArray:addObject(bezierAction)
	actionArray:addObject(fadeOut)
	actionArray:addObject(callback)
	local  action = CCSequence:create(actionArray)
    
    local expLabel = LabelBMFont:create()
    expLabel:setFntFile("Fonts/chengse.fnt")
    Log("expUp===="..info.iGetExp)
    if bKnock then
      local str = FormatString("GadAnimal_Knock",info.iGetExp)
      expLabel:setText(str)
    	--expLabel = CompLabel:GetDefaultCompLabel(FormatString("GadAnimal_Knock",iGetExp),192);
    else
      expLabel:setText("+ "..info.iGetExp)
    	--expLabel = CompLabel:GetDefaultCompLabel(FormatString("GadAnimal_LifeAtt_Exp",iGetExp),192);
    end
    expLabel:runAction(action)
    
    expLabel:setPosition( ccp(animaltionlayoutPositionX,animaltionlayoutPositionY))
	expLabel:setAnchorPoint(ccp(0.5,0.5))
	widget:addChild(expLabel,500,500)
end 
