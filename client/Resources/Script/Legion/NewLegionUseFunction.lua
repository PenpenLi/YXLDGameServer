--                            _ooOoo_  
--                           o8888888o  
--                           88" . "88  
--                           (| -_- |)  
--                            O\ = /O  
--                        ____/`---'\____  
--                      .   ' \\| |// `.  
--                       / \\||| : |||// \  
--                     / _||||| -:- |||||- \  
--                       | | \\\ - /// | |  
--                     | \_| ''\---/'' | |  
--                      \ .-\__ `-` ___/-. /  
--                   ___`. .' /--.--\ `. . __  
--                ."" '< `.___\_<|>_/___.' >'"".  
--               | | : `- \`.;`\ _ /`;.`/ - ` : | |  
--                 \ \ `-. \_ __\ /__ _/ .-` / /  
--         ======`-.____`-.___\_____/___.-`____.-'======  
--                            `=---='  
--  
--         .............................................  
--                  ������¥                  BUG���� 

--[[" 
      ������Ҫ�õ��ĺ��� Begin
"]]

function NewLegion_RankImageFont(imagelayout,fontlayout,rankIndex)
   if rankIndex <= 3 then
      imagelayout:setVisible(true)
      fontlayout:setVisible(false)
      imagelayout:loadTexture("jingjichang/font_7_0"..rankIndex..".png")
   else 
      imagelayout:setVisible(false)
      fontlayout:setVisible(true)
      fontlayout:setText(rankIndex)
   end 
end 

function NewLegion_GetImageView(ImageId)
   return "Icon/Skill/"..ImageId..".png"
end

--[[" 
      ������Ҫ�õ��ĺ��� End
"]]