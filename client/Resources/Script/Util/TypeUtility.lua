--[[
����ת������
]]--

--ȡ����
function ToInt( luaNumber )
	if( luaNumber <= 0 )then
		return math.ceil( luaNumber );
	end
	if( math.ceil( luaNumber ) == luaNumber)then
		return math.ceil( luaNumber );
	else
		return math.ceil( luaNumber ) - 1;
	end
end
