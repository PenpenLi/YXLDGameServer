function CashCow_Create()
    local tab = GameServer_pb.CMD_COINTREE_SHAKE_QUERY_CS();
    tab.enType = 1
    Packet_Full(GameServer_pb.CMD_COINTREE_SHAKE_QUERY, tab);
    ShowWaiting()
end
function CashCow_CreateLayer(pkg)
    local info = GameServer_pb.CMD_COINTREE_SHAKE_QUERY_SC()
    info:ParseFromString(pkg)
    Log("info===="..tostring(info))
    EndWaiting()

    if ( info.detail.enType ==  2)then
        --ʮ��������
        CashCow_ManyTimes(info)
        return 
    end
    CashCow_RefreshData(info.detail)
end
--ˢ�µ�������
function CashCow_RefreshData(detail)
    local widget = UI_GetBaseWidgetByName("CashCow")
    if widget == nil then
        widget = UI_CreateBaseWidgetByFileName("CashCow.json")
        UI_GetUIImageView(widget, 4670552):setVisible(false)
    else
        UI_GetUIImageView(widget, 4670552):setVisible(true)
    end
    UI_GetUILayout(widget, 4670515):addTouchEventListener(PublicCallBackWithNothingToDo)

    local function close(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            UI_CloseCurBaseWidget(EUIOpenAction_None)
        end
    end

    UI_GetUIButton(widget, 4670524):addTouchEventListener(close)
    --���տ�ҡ
    UI_GetUILabel(widget, 4670637):setText(detail.iRemaindShakeTimes.."/"..detail.iTotalShakeTimes)
    --ҡһ��
    local function once(sender,eventType)
        if (eventType == TOUCH_EVENT_ENDED) then
            CashCow_Konck(1)
        end
    end
    --����ҡ
    local function ManyTimes(sender,eventType)
        if (eventType == TOUCH_EVENT_ENDED) then
            local tab = GameServer_pb.CMD_COINTREE_SHAKE_QUERY_CS();
            tab.enType = 2
            Packet_Full(GameServer_pb.CMD_COINTREE_SHAKE_QUERY, tab);
            ShowWaiting()
        end
    end
    --�鿴VIp
    local function vip(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            VIPInfo()
        end
    end
    
    local isHaveEnoughTime = nil
    if detail.iRemaindShakeTimes>0 then
        isHaveEnoughTime = true
    else
        isHaveEnoughTime = false
    end
    print("-----------------------1----------------------")
    if isHaveEnoughTime == true then
        local layout = UI_GetUILayout(widget, 4687742)
        --�˴�Ԫ������
        UI_GetUILabel(layout, 4670542):setText(detail.iCost)
        --�˴��ܻ�õ�ͭǮ
        UI_GetUILabel(layout, 4670544):setText(detail.iGet)
       
        --ҡһ��
        UI_GetUIButton(widget, 4670547):addTouchEventListener(once)
        UI_GetUIButton(widget, 4670547):setTitleText(FormatString("CrashCowOnce"))
        --����ҡ
        UI_GetUIButton(widget, 4670550):addTouchEventListener(ManyTimes)
        UI_GetUIButton(widget, 4670550):setTitleText(FormatString("CrashCowN"))

        layout:setVisible(true)
        UI_GetUILayout(widget, 4670652):setVisible(false)
        
    else
        UI_GetUILayout(widget, 4670652):setVisible(true)
        UI_GetUILayout(widget, 4687742):setVisible(false)

        --�ر�
        UI_GetUIButton(widget, 4670547):addTouchEventListener(close)
        UI_GetUIButton(widget, 4670547):setTitleText(FormatString("CrashCowClose"))
        --�鿴VIP
        UI_GetUIButton(widget, 4670550):addTouchEventListener(vip)
        UI_GetUIButton(widget, 4670550):setTitleText(FormatString("CrashCowVIP"))
    end
end
--����ҡ
function CashCow_ManyTimes(info)
    local widget = UI_CreateBaseWidgetByFileName("CashCowN.json") 
    UI_GetUILayout(widget, 4670629):addTouchEventListener(PublicCallBackWithNothingToDo)
    local function close(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            UI_CloseCurBaseWidget()
        end
    end
    UI_GetUIButton(widget, 4670627):addTouchEventListener(close)
    --ҡһҡ�Ĵ���
    UI_GetUILabel(widget, 4670602):setText(info.iCanShakeTimes)
    --���ĵ�Ԫ��
    UI_GetUILabel(UI_GetUIImageView(widget, 4670608), 4670612):setText(info.detail.iCost)
    --��õ�ͭ��
    UI_GetUILabel(UI_GetUIImageView(widget, 4670617), 4670620):setText(info.detail.iGet)
    --ȷ������
    local function determine(sender,eventType)
        if eventType == TOUCH_EVENT_ENDED then
            UI_CloseCurBaseWidget()
            CashCow_Konck(2)
        end
    end
    UI_GetUIButton(widget, 4670621):addTouchEventListener(determine)
end
--���θ���ҡǮ�İ�ť�ĵ��״̬
function CashCow_CashSate(isTouchEnable)
    local widget = UI_GetBaseWidgetByName("CashCow") 
    if widget then
        UI_GetUIButton(widget, 4670547):setTouchEnabled(isTouchEnable)
        UI_GetUIButton(widget, 4670550):setTouchEnabled(isTouchEnable)
    end
end
--��ʾ��ҡ����ͭ��
function CashCow_AddAward(pkg)

    local info = GameServer_pb.CMD_COINTREE_SHAKE_SC()
    info:ParseFromString(pkg)
    Log("info===="..tostring(info))
    EndWaiting()

    CashCow_CashSate(false)
    local widget = UI_GetBaseWidgetByName("CashCow")
    if widget ~= nil then
        local num = 1
        local listView = UI_GetUIListView(widget, 4670554)
        --�����ʾ�Ķ���
        local function PlayAniamtion(oneLine)
            local waitTime = 0.01
            if info.szShakeResoult[num].iKnock>1 then
                UI_GetUILabelBMFont(oneLine, 4670632):setScale(3)
                UI_GetUILabelBMFont(oneLine, 4670632):setVisible(true)

                local actionArry = CCArray:create()
                local scale = CCScaleTo:create(0.15,1)
                actionArry:addObject(scale)
                local seqaction = CCSequence:create(actionArry)

                UI_GetUILabelBMFont(oneLine, 4670632):runAction(seqaction)
                waitTime = waitTime+0.15
            end   
              
            local panel = UI_GetUILayout(oneLine, 4691716)     
            
            local function ShowMessage()
                panel:setVisible(true)
            end

            local actionArry_ = CCArray:create()
            local delayTime = CCDelayTime:create(waitTime)
            actionArry_:addObject(delayTime)
            local callback = CCCallFuncN:create(ShowMessage)
            actionArry_:addObject(callback)
            local fadeIn =  CCFadeIn:create(0.3)
            actionArry_:addObject(fadeIn)

            local seqaction_ = CCSequence:create(actionArry_)

            panel:runAction(seqaction_)

            return waitTime
        end
        -- ��ӳ�ȡ���
        local function addMessage()

            if num > #info.szShakeResoult then
                CashCow_CashSate(true)
                return
            end

            local oneLine = UI_GetUILayout(widget, 4670556):clone()
            oneLine:setVisible(true)
            local panel = UI_GetUILayout(oneLine, 4691716)
            panel:setVisible(false)
            UI_GetUILabelBMFont(oneLine, 4670632):setVisible(false)
            --����
            UI_GetUILabel(panel, 4670564):setText(info.szShakeResoult[num].iCost)
            --���
            UI_GetUILabel(panel, 4670574):setText(info.szShakeResoult[num].iGet)
            --����
            if info.szShakeResoult[num].iKnock>1 then
                UI_GetUILabelBMFont(oneLine, 4670632):setText(FormatString("CrashCowCrit",info.szShakeResoult[num].iKnock))
            end
            listView:pushBackCustomItem(oneLine)

            local waitTime = PlayAniamtion(oneLine)

            print("waitTime ==========================="..waitTime)

            local actionArry = CCArray:create()
            local delayTime = CCDelayTime:create(0.01)
            actionArry:addObject(delayTime)
            local callback = CCCallFuncN:create(CashCow_listViewJump)
            actionArry:addObject(callback)
            local delayTime_ = CCDelayTime:create(waitTime+0.4)
            actionArry:addObject(delayTime_)
            local callback_ = CCCallFuncN:create(addMessage)
            actionArry:addObject(callback_)
            local seqaction = CCSequence:create(actionArry)

            listView:runAction(seqaction)
            
            num = num+1
        end

        addMessage()
    end

    CashCow_RefreshData(info.detail)
end
--�ƶ�������һ������
function CashCow_listViewJump()
    local widget = UI_GetBaseWidgetByName("CashCow")
    if widget ~= nil then
        local listView = UI_GetUIListView(widget, 4670554)
        listView:jumpToBottom()
    end
end

--ҡ
function CashCow_Konck(konckType)
    local tab = GameServer_pb.CMD_COINTREE_SHAKE_CS();
    tab.enType = konckType
    Packet_Full(GameServer_pb.CMD_COINTREE_SHAKE, tab);
    ShowWaiting()
end
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_COINTREE_SHAKE_QUERY, "CashCow_CreateLayer" );
ScriptSys:GetInstance():RegisterScriptFunc( GameServer_pb.CMD_COINTREE_SHAKE, "CashCow_AddAward" );