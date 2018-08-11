--[[
�ַ������ú���
]]--

-- �ֽ��ַ���,�Կո�ֿ�,����һ���ַ�����
-- ����:��splitChar�ָ������ַ���
function SplitString( str, splitChar )
	local strTab = {}
	local len = string.len( str )
	local tmpStr = "";
	if( splitChar == nil )then
		splitChar = " ";
	end
	local space = string.byte( splitChar );
	--Log( "space = "..space ); --32
	for i=1,len do
		if( string.byte(str,i) == space )then
			--Log( "tmpStr = "..tmpStr );
			if( string.len( tmpStr ) > 0 )then
				strTab[#strTab+1] = tmpStr;
			end
			tmpStr = "";
		else
			tmpStr = tmpStr..string.char(string.byte(str,i));
		end
	end
	if( string.len( tmpStr ) > 0 )then
		strTab[#strTab+1] = tmpStr;
		--Log( "tmpStr = "..tmpStr );
	end
	return strTab;
end

-- ��ʽ���ַ���
function FormatString( key, arg1, arg2, arg3, arg4, arg5, arg6 )
	if( arg1 == nil )then
		return StringMgr:GetInstance():FormatString( key )
	end
	local argTable = {}
	if( arg1 )then
		argTable[#argTable+1] = arg1
		if( arg2 )then
			argTable[#argTable+1] = arg2
			if( arg3 )then
				argTable[#argTable+1] = arg3
				if( arg4 )then
					argTable[#argTable+1] = arg4
					if( arg5 )then
						argTable[#argTable+1] = arg5
						if( arg6 )then
							argTable[#argTable+1] = arg6
						end
					end
				end
			end
		end
	end
	local args = vector_Var_:new_local();
	for i,arg in ipairs(argTable) do
		local newArg = Var:new_local()
		if( type(arg) == "number" )then
			newArg:InitFromString( ETypeId_double, tostring(arg) )
		elseif( type(arg) == "string" )then
			newArg:InitFromString( ETypeId_string, arg )
		end
		args:push_back( newArg )
	end
	return StringMgr:GetInstance():FormatStringArgs( key, args )
end

-- ���绰�����Ƿ�Ϸ�
function String_CheckPhoneNo( str )
	if( string.find( str, "1%d%d%d%d%d%d%d%d%d%d" ) )then
		return true
	end
	return false
end

-- ��������Ƿ�Ϸ�
function String_CheckEmail( str )
	if( string.find( str, "%w+@%w+[.]%w+" ) )then
		return true
	end
	return false
end

-- ������֤�Ƿ�Ϸ�
function String_CheckIdCard( str )
	local len = string.len( str )
	if( len == 15 )then
		-- 15λȫ������
		if( string.find( str, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d" ) )then
			return true
		end
	elseif( len == 18 )then
		-- 18λ�����һλ������X
		if( string.find( str, "%d%d%d%d%d%d19%d%d%d%d%d%d%d%d%d%w" ) )then
			return true
		end
		if( string.find( str, "%d%d%d%d%d%d20%d%d%d%d%d%d%d%d%d%w" ) )then
			return true
		end
	end
	return false
end

-- ����û����Ƿ�Ϸ�(3-14λӢ�Ļ�����)
function String_CheckUserName( str )
	local len = string.len( str )
	if( len < 3 or len > 14 )then
		return false
	end
	if( string.find( str, "%W" ) )then
		return false
	end
	-- ��ֹ�����"youke"��ͷ���˺�
	if( string.find( str, "youke%d+" ) )then
		return false
	end
	return true
end

-- ��������Ƿ�Ϸ�(6-14λӢ�Ļ�����)
function String_CheckUserPwd( str )
	local len = string.len( str )
	if( len < 6 or len > 14 )then
		return false
	end
	if( string.find( str, "%W" ) )then
		return false
	end
	return true
end
