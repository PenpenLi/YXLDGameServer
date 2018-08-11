// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 4.6.0 by WSRD Tencent.
// Generated from `Push.jce'
// **********************************************************************

#include "Push.h"
#include "jce/wup.h"
#include "servant/BaseF.h"

using namespace wup;

namespace ServerEngine
{

    taf::Int32 PushProxy::doNotifyLoginOff(taf::Int64 iConnId, const std::string &sMsgPack, const map<string, string> &context)
    {
        taf::JceOutputStream<taf::BufferWriter> _os;
        _os.write(iConnId, 1);
        _os.write(sMsgPack, 2);
        taf::ResponsePacket rep;
        std::map<string, string> status;
        taf_invoke(taf::JCENORMAL,"doNotifyLoginOff", _os.getByteBuffer(), context, status, rep);
        taf::JceInputStream<taf::BufferReader> _is;
        _is.setBuffer(rep.sBuffer);
        taf::Int32 _ret;
        _is.read(_ret, 0, true);
        return _ret;
    }

    void Push::async_response_doNotifyLoginOff(taf::JceCurrentPtr current, taf::Int32 _ret)
    {
        if (current->getRequestVersion() == WUPVERSION || current->getRequestVersion() == WUPVERSION2)
        {
            UniAttribute<taf::BufferWriter, taf::BufferReader>  tafAttr;
            tafAttr.setVersion(current->getRequestVersion());
            tafAttr.put("", _ret);

            vector<char> sWupResponseBuffer;
            tafAttr.encode(sWupResponseBuffer);
            current->sendResponse(taf::JCESERVERSUCCESS, sWupResponseBuffer);
        }
        else
        {
            taf::JceOutputStream<taf::BufferWriter> _os;
            _os.write(_ret, 0);

            current->sendResponse(taf::JCESERVERSUCCESS, _os.getByteBuffer());
        }
    }

    void PushProxy::async_doNotifyLoginOff(PushPrxCallbackPtr callback,taf::Int64 iConnId,const std::string &sMsgPack,const map<string, string>& context)
    {
        taf::JceOutputStream<taf::BufferWriter> _os;
        _os.write(iConnId, 1);
        _os.write(sMsgPack, 2);
        std::map<string, string> status;
        taf_invoke_async(taf::JCENORMAL,"doNotifyLoginOff", _os.getByteBuffer(), context, status, callback);
    }

    taf::Int32 PushProxy::doPush(taf::Int64 iConnId, const std::string &sMsgPack, const map<string, string> &context)
    {
        taf::JceOutputStream<taf::BufferWriter> _os;
        _os.write(iConnId, 1);
        _os.write(sMsgPack, 2);
        taf::ResponsePacket rep;
        std::map<string, string> status;
        taf_invoke(taf::JCENORMAL,"doPush", _os.getByteBuffer(), context, status, rep);
        taf::JceInputStream<taf::BufferReader> _is;
        _is.setBuffer(rep.sBuffer);
        taf::Int32 _ret;
        _is.read(_ret, 0, true);
        return _ret;
    }

    void Push::async_response_doPush(taf::JceCurrentPtr current, taf::Int32 _ret)
    {
        if (current->getRequestVersion() == WUPVERSION || current->getRequestVersion() == WUPVERSION2)
        {
            UniAttribute<taf::BufferWriter, taf::BufferReader>  tafAttr;
            tafAttr.setVersion(current->getRequestVersion());
            tafAttr.put("", _ret);

            vector<char> sWupResponseBuffer;
            tafAttr.encode(sWupResponseBuffer);
            current->sendResponse(taf::JCESERVERSUCCESS, sWupResponseBuffer);
        }
        else
        {
            taf::JceOutputStream<taf::BufferWriter> _os;
            _os.write(_ret, 0);

            current->sendResponse(taf::JCESERVERSUCCESS, _os.getByteBuffer());
        }
    }

    void PushProxy::async_doPush(PushPrxCallbackPtr callback,taf::Int64 iConnId,const std::string &sMsgPack,const map<string, string>& context)
    {
        taf::JceOutputStream<taf::BufferWriter> _os;
        _os.write(iConnId, 1);
        _os.write(sMsgPack, 2);
        std::map<string, string> status;
        taf_invoke_async(taf::JCENORMAL,"doPush", _os.getByteBuffer(), context, status, callback);
    }

    PushProxy* PushProxy::taf_hash(int64_t key)
    {
        return (PushProxy*)ServantProxy::taf_hash(key);
    }

    static ::std::string __ServerEngine__Push_all[]=
    {
        "doNotifyLoginOff",
        "doPush"
    };

    int PushPrxCallback::onDispatch(taf::ReqMessagePtr msg)
    {
        pair<string*, string*> r = equal_range(__ServerEngine__Push_all, __ServerEngine__Push_all+2, msg->request.sFuncName);
        if(r.first == r.second) return taf::JCESERVERNOFUNCERR;
        switch(r.first - __ServerEngine__Push_all)
        {
            case 0:
            {
                if (msg->response.iRet != taf::JCESERVERSUCCESS)
                {
                    callback_doNotifyLoginOff_exception(msg->response.iRet);

                    return msg->response.iRet;
                }
                taf::JceInputStream<taf::BufferReader> _is;

                _is.setBuffer(msg->response.sBuffer);
                taf::Int32 _ret;
                _is.read(_ret, 0, true);

                callback_doNotifyLoginOff(_ret);
                return taf::JCESERVERSUCCESS;

            }
            case 1:
            {
                if (msg->response.iRet != taf::JCESERVERSUCCESS)
                {
                    callback_doPush_exception(msg->response.iRet);

                    return msg->response.iRet;
                }
                taf::JceInputStream<taf::BufferReader> _is;

                _is.setBuffer(msg->response.sBuffer);
                taf::Int32 _ret;
                _is.read(_ret, 0, true);

                callback_doPush(_ret);
                return taf::JCESERVERSUCCESS;

            }
        }
        return taf::JCESERVERNOFUNCERR;
    }

    int Push::onDispatch(taf::JceCurrentPtr _current, vector<char> &_sResponseBuffer)
    {
        pair<string*, string*> r = equal_range(__ServerEngine__Push_all, __ServerEngine__Push_all+2, _current->getFuncName());
        if(r.first == r.second) return taf::JCESERVERNOFUNCERR;
        switch(r.first - __ServerEngine__Push_all)
        {
            case 0:
            {
                taf::JceInputStream<taf::BufferReader> _is;
                _is.setBuffer(_current->getRequestBuffer());
                taf::Int64 iConnId;
                std::string sMsgPack;
                if (_current->getRequestVersion() == WUPVERSION || _current->getRequestVersion() == WUPVERSION2)
                {
                    UniAttribute<taf::BufferWriter, taf::BufferReader>  tafAttr;
                    tafAttr.setVersion(_current->getRequestVersion());
                    tafAttr.decode(_current->getRequestBuffer());
                    tafAttr.get("iConnId", iConnId);
                    tafAttr.get("sMsgPack", sMsgPack);
                }
                else
                {
                    _is.read(iConnId, 1, true);
                    _is.read(sMsgPack, 2, true);
                }
                taf::Int32 _ret = doNotifyLoginOff(iConnId,sMsgPack, _current);
                if(_current->isResponse())
                {
                    if (_current->getRequestVersion() == WUPVERSION || _current->getRequestVersion() == WUPVERSION2)
                    {
                        UniAttribute<taf::BufferWriter, taf::BufferReader>  tafAttr;
                        tafAttr.setVersion(_current->getRequestVersion());
                        tafAttr.put("", _ret);
                        tafAttr.encode(_sResponseBuffer);
                    }
                    else
                    {
                        taf::JceOutputStream<taf::BufferWriter> _os;
                        _os.write(_ret, 0);
                        _os.swap(_sResponseBuffer);
                    }
                }
                return taf::JCESERVERSUCCESS;

            }
            case 1:
            {
                taf::JceInputStream<taf::BufferReader> _is;
                _is.setBuffer(_current->getRequestBuffer());
                taf::Int64 iConnId;
                std::string sMsgPack;
                if (_current->getRequestVersion() == WUPVERSION || _current->getRequestVersion() == WUPVERSION2)
                {
                    UniAttribute<taf::BufferWriter, taf::BufferReader>  tafAttr;
                    tafAttr.setVersion(_current->getRequestVersion());
                    tafAttr.decode(_current->getRequestBuffer());
                    tafAttr.get("iConnId", iConnId);
                    tafAttr.get("sMsgPack", sMsgPack);
                }
                else
                {
                    _is.read(iConnId, 1, true);
                    _is.read(sMsgPack, 2, true);
                }
                taf::Int32 _ret = doPush(iConnId,sMsgPack, _current);
                if(_current->isResponse())
                {
                    if (_current->getRequestVersion() == WUPVERSION || _current->getRequestVersion() == WUPVERSION2)
                    {
                        UniAttribute<taf::BufferWriter, taf::BufferReader>  tafAttr;
                        tafAttr.setVersion(_current->getRequestVersion());
                        tafAttr.put("", _ret);
                        tafAttr.encode(_sResponseBuffer);
                    }
                    else
                    {
                        taf::JceOutputStream<taf::BufferWriter> _os;
                        _os.write(_ret, 0);
                        _os.swap(_sResponseBuffer);
                    }
                }
                return taf::JCESERVERSUCCESS;

            }
        }
        return taf::JCESERVERNOFUNCERR;
    }


}
