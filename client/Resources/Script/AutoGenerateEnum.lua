--[[
	�ڴ�����c++ͷ�ļ�
]]--

local cleintPath = "../Classes/";

local fileList = 
{
	cleintPath.."Enum/FmComponentEnum.h",
	cleintPath.."Enum/FmNumricEnum.h",
	cleintPath.."Enum/FmEntityRenderEnum.h",
	cleintPath.."Enum/FmCommonEnum.h",
}



--[[
	����c++��ö���ļ��Զ�����lua�ļ�
]]--
function EnumCppToLua( cppFile, outputPath )
	local luaStrings = "";
	local lastEnumValue = -1;
	local findEnum = false;
	local findLeftBracket = false;
	for line in io.lines( cppFile ) do
		--print( line );
		line = RemoveComment( line );	-- ɾ��ע��
		line = StringUtil:Trim( line );	-- ɾ��ͷβ�Ŀո�
		--print( line );
		-- ���ҵ�Enum�ؼ���
		if( findEnum == false )then
			local beginIdx,endIdx = string.find( line, "enum" );
			if( beginIdx ~= nil and beginIdx == 1 )then
				findEnum = true;
				-- ����������
				beginIdx,endIdx = string.find( line, "{" );
				if( beginIdx ~= nil )then
					findLeftBracket = true;
				end
			end
		else
			-- ����������
			if( findLeftBracket == false )then
				local beginIdx,endIdx = string.find( line, "{" );
				if( beginIdx ~= nil )then
					findLeftBracket = true;
				end
			else
				-- ����������
				local beginIdx,endIdx = string.find( line, "}" );
				if( beginIdx ~= nil )then
					-- ö�ٽ���
					lastEnumValue = -1;
					findEnum = false;
					findLeftBracket = false;
					luaStrings = luaStrings .. "\n";
				else
					-- ��һ����ö��ֵ
					beginIdx,endIdx = string.find( line, "," );
					-- ���Ų��Ǳ����
					if( beginIdx == nil )then
						beginIdx = string.len( line ) + 1;
					end
					if( beginIdx ~= nil )then
						line = string.sub( line, 1, beginIdx-1 );
						beginIdx,endIdx = string.find( line, "=" );
						local enumName = "";
						local enumValue = 0;
						-- �о��帳ֵ��
						if( beginIdx ~= nil )then
							enumName = string.sub( line, 1, beginIdx-1 );
							enumName = StringUtil:Trim( enumName );
							if( string.len(enumName) > 0 )then
								local enumValueString = string.sub( line, endIdx+1 );
								enumValueString = StringUtil:Trim( enumValueString );
								enumValue = tonumber( enumValueString );
								lastEnumValue = enumValue;
							end
						-- ������ֵ��
						else
							enumName = StringUtil:Trim( line );
							if( string.len(enumName) > 0 )then
								enumValue = lastEnumValue + 1;
								lastEnumValue = enumValue;
							end
						end
						if( string.len(enumName) > 0 )then
							if( enumValue == nil )then
								print("enumValue == nil enumName="..enumName);
							end
							luaStrings = luaStrings .. enumName .. "=" .. enumValue .. "\n";
						end
						--print( string.format( "%s = %d", enumName, enumValue or -100 ) );
					end
				end
			end
		end
	end
	
	local fullName,baseName,pathName = StringUtil:SplitFilename( cppFile, nil, nil );
	baseName = string.sub( baseName, 1, string.len(baseName)-2 ); -- ȥ��.h
	local luaFileName = baseName..".lua";
	if( outputPath ~= nil )then
		luaFileName = outputPath.."/"..luaFileName;
	end
	local f = io.open( luaFileName, "w+" );
	if( f ~= nil )then
		f:write( luaStrings );
		f:flush();
		f:close();
	else
		print( string.format("open file error:%s", luaFileName) );
	end
end

-- ȥ��ע��
function RemoveComment( line )
	local beginIdx,endIdx = string.find( line, "//" );
	if( beginIdx ~= nil )then
		return string.sub( line, 1, beginIdx-1 );
	end
	return line;
end




local luaStrings = "";

for index,cppFile in pairs( fileList ) do
	-- cppFile = cppFile;
	local fullName,baseName,pathName = StringUtil:SplitFilename( cppFile, nil, nil );
	baseName = string.sub( baseName, 1, string.len(baseName)-2 ); -- ȥ��.h
	local luaFileName = baseName..".lua";
	EnumCppToLua( cppFile );
	
	luaStrings = luaStrings.."LoadFile('Enum/"..luaFileName.."')\n";
	
	os.execute( string.format("copy .\\%s .\\..\\Resources\\Script\\Enum\\", luaFileName) );
	os.execute( string.format("del .\\%s", luaFileName) );
end

local f = io.open( "EnumAutoGenerate.lua", "w+" );
if( f ~= nil )then
	f:write( luaStrings );
	f:flush();
	f:close();
else
	print( string.format("open file error:%s", "EnumAutoGenerate.lua") );
end

os.execute( string.format("copy .\\%s .\\..\\Resources\\Script\\Enum\\", "EnumAutoGenerate.lua" ) );
os.execute( string.format("del .\\%s", "EnumAutoGenerate.lua") );
