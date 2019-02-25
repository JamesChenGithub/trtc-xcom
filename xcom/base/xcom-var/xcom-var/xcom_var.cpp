//
//  xcom_var.cpp
//  xcom_var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#include "xcom_var.h"
#include <iostream>
#include "xcom_var_util.h"
#include <exception>
namespace xcom {
#ifdef __cplusplus
    //    extern "C" {
#endif
    //==============================
    static int varcout = 0;
    xcom_var::~xcom_var()
    {
        printf("xcom_var [%d] dealloc : %p \n", --varcout, this);
        reset();
    }
#define kDefault_Xcom_Var_Value = {.int32_val{0}}
    xcom_var::xcom_var()
    {
        printf("xcom_var [%d]  malloc : %p\n", ++varcout, this);
        this->type = xcom_vtype_null;
    }
    
    void xcom_var::reset()
    {
        
        switch(this->type)
        {
            case xcom_vtype_array:
            {
                if (this->obj.array_val != nullptr)
                {
                    for (int i = 0; i < this->obj.array_val->size(); i++) {
                        (*this->obj.array_val)[i] = nullptr;
                    }
                    delete this->obj.array_val;
                    this->obj.array_val = nullptr;
                }
                
                break;
            }
            case xcom_vtype_dict:
            {
                if (this->obj.dict_val != nullptr)
                {
                    for (auto it = this->obj.dict_val->begin(); it != this->obj.dict_val->end(); it++) {
                        it->second = nullptr;
                    }
                    
                    delete this->obj.dict_val;
                    this->obj.dict_val = nullptr;
                }
                break;
            }
            case xcom_vtype_map:
            {
                if (this->obj.map_val != nullptr)
                {
                    for (auto it = this->obj.map_val->begin(); it != this->obj.map_val->end(); it++) {
                        it->second = nullptr;
                    }
                    
                    delete this->obj.map_val;
                    this->obj.map_val = nullptr;
                }
                break;
            }
                
            case xcom_vtype_bytes:
            {
                if (this->obj.buf_val != nullptr)
                {
                    delete this->obj.buf_val;
                    this->obj.buf_val = nullptr;
                }
                break;
            }
            case xcom_vtype_vptr:
            {
                this->obj.vptr_val = nullptr;
                break;
            }
            case xcom_vtype_func:
            {
                if (this->obj.func_val != nullptr)
                {
                    delete this->obj.func_val;
                    this->obj.func_val = nullptr;
                }
                break;
            }
            case xcom_vtype_null:
            case xcom_vtype_bool:
            case xcom_vtype_int8:
            case xcom_vtype_uint8:
            case xcom_vtype_int16:
            case xcom_vtype_uint16:
            case xcom_vtype_int32:
            case xcom_vtype_uint32:
            case xcom_vtype_int64:
            case xcom_vtype_uint64:
            case xcom_vtype_float:
            case xcom_vtype_double:
            case xcom_vtype_string:
            case xcom_vtype_ref:
                
            default:
                break;
        }
        memset(&(this->obj), 0, sizeof(xcom_var_value));
        this->type = xcom_vtype_null;
        
    }
    
    void xcom_var::reset(const xcom_var &var)
    {
        this->reset();
        this->type = var.type;
        switch(var.type)
        {
            case xcom_vtype_array:
            {
                if (var.obj.array_val)
                {
                    this->obj.array_val = new xcom_var_array;
                    auto it = var.obj.array_val->begin();
                    while (it != var.obj.array_val->end()) {
                        xcom_var_ptr cpy(new xcom_var(*it));
                        this->obj.array_val->emplace_back(cpy);
                        it++;
                    }
                }
                
                break;
            }
            case xcom_vtype_dict:
            {
                if (var.obj.dict_val)
                {
                    this->obj.dict_val = new xcom_var_dict;
                    auto it = var.obj.dict_val->begin();
                    while (it != var.obj.dict_val->end()) {
                        
                        xcom_var_ptr sec(new xcom_var(*(it->second)));
                        this->obj.dict_val->push_back(std::make_pair(it->first, sec));
                        it++;
                    }
                }
                break;
            }
            case xcom_vtype_map:
            {
                if (var.obj.map_val)
                {
                    this->obj.map_val = new xcom_var_map;
                    auto it = var.obj.map_val->begin();
                    while (it != var.obj.map_val->end()) {
                        
                        xcom_var_ptr sec(new xcom_var(*(it->second)));
                        this->obj.map_val->insert(std::make_pair(it->first, sec));
                        it++;
                    }
                }
                break;
            }
                
            case xcom_vtype_bytes:
            {
                if (var.obj.buf_val)
                {
                    this->obj.buf_val = new xcom_var_buf(var.obj.buf_val->buf, var.obj.buf_val->len);
                }
                break;
            }
            case xcom_vtype_vptr:
            {
                if (var.obj.vptr_val)
                {
                    this->obj.vptr_val = var.obj.vptr_val;
                }
                break;
            }
            case xcom_vtype_func: {
                if (this->obj.func_val != nullptr)
                {
                    delete this->obj.func_val;
                    this->obj.func_val = nullptr;
                }
                this->obj.func_val = var.obj.func_val;
                break;
            }
                
            case xcom_vtype_null:  break;
            case xcom_vtype_bool: { this->obj.bool_val = var.obj.bool_val; break; }
            case xcom_vtype_int8: { this->obj.int8_val = var.obj.int8_val; break; }
            case xcom_vtype_uint8: { this->obj.uint8_val = var.obj.uint8_val; break; }
            case xcom_vtype_int16: { this->obj.int16_val = var.obj.int16_val; break; }
            case xcom_vtype_uint16: { this->obj.uint16_val = var.obj.uint16_val; break; }
            case xcom_vtype_int32: { this->obj.int32_val = var.obj.int32_val; break; }
            case xcom_vtype_uint32: { this->obj.uint32_val = var.obj.uint32_val; break; }
            case xcom_vtype_int64: { this->obj.int64_val = var.obj.int64_val; break; }
            case xcom_vtype_uint64: { this->obj.uint64_val = var.obj.uint64_val; break; }
            case xcom_vtype_float: { this->obj.float_val = var.obj.float_val; break; }
            case xcom_vtype_double: { this->obj.double_val = var.obj.double_val; break; }
            case xcom_vtype_string: { this->obj.string_val = var.obj.string_val; break; }
            case xcom_vtype_ref: { this->obj.ref_val = var.obj.ref_val; break; }
                
                
            default:
            {
                break;
            }
        }
        
        
        
    }
    
    void xcom_var::reset(xcom_var &&var)
    {
        this->reset();
        this->type = var.type;
        switch(var.type)
        {
            case xcom_vtype_array:
            {
                if (var.obj.array_val)
                {
                    this->obj.array_val = var.obj.array_val;
                    var.obj.array_val = nullptr;
                }
                
                break;
            }
            case xcom_vtype_dict:
            {
                if (var.obj.dict_val)
                {
                    this->obj.dict_val = var.obj.dict_val;
                    var.obj.dict_val = nullptr;
                }
                break;
            }
            case xcom_vtype_map:
            {
                if (var.obj.map_val)
                {
                    this->obj.map_val = var.obj.map_val;
                    var.obj.map_val = nullptr;
                }
                break;
            }
            case xcom_vtype_vptr:
            {
                if (var.obj.vptr_val) {
                    this->obj.vptr_val = var.obj.vptr_val;
                    var.obj.vptr_val = nullptr;
                }
                break;
            }
            case xcom_vtype_bytes:
            {
                if (var.obj.buf_val)
                {
                    this->obj.buf_val = var.obj.buf_val;
                    var.obj.buf_val = nullptr;
                }
                break;
            }
            case xcom_vtype_func: {
                if (this->obj.func_val != nullptr)
                {
                    delete this->obj.func_val;
                    this->obj.func_val = nullptr;
                }
                this->obj.func_val = std::move(var.obj.func_val);
                var.obj.func_val = nullptr;
                break; }
                
            case xcom_vtype_null:  break;
            case xcom_vtype_bool: { this->obj.bool_val = var.obj.bool_val; break; }
            case xcom_vtype_int8: { this->obj.int8_val = var.obj.int8_val; break; }
            case xcom_vtype_uint8: { this->obj.uint8_val = var.obj.uint8_val; break; }
            case xcom_vtype_int16: { this->obj.int16_val = var.obj.int16_val; break; }
            case xcom_vtype_uint16: { this->obj.uint16_val = var.obj.uint16_val; break; }
            case xcom_vtype_int32: { this->obj.int32_val = var.obj.int32_val; break; }
            case xcom_vtype_uint32: { this->obj.uint32_val = var.obj.uint32_val; break; }
            case xcom_vtype_int64: { this->obj.int64_val = var.obj.int64_val; break; }
            case xcom_vtype_uint64: { this->obj.uint64_val = var.obj.uint64_val; break; }
            case xcom_vtype_float: { this->obj.float_val = var.obj.float_val; break; }
            case xcom_vtype_double: { this->obj.double_val = var.obj.double_val; break; }
            case xcom_vtype_string: { this->obj.string_val = var.obj.string_val; var.obj.string_val = ""; break; }
            case xcom_vtype_ref: { this->obj.ref_val = var.obj.ref_val; var.obj.ref_val = nullptr; break; }
                
                
            default:
            {
                break;
            }
        }
        
        var.reset();
    }
    
    
    //================
    const char *xcom_var::to_var_json() const
    {
        std::string restr = "";
        std::string typestr = xcom_var_type_string(this->type);
        std::string valstr = "" ;
        switch(this->type)
        {
            case xcom_vtype_null: { valstr = "NULL"; break; };
            case xcom_vtype_bool: { valstr = this->bool_val() ? "true" : "false"; break; };
            case xcom_vtype_int8: { valstr = std::to_string(this->int8_val()); break;};
            case xcom_vtype_uint8: { valstr = std::to_string(this->uint8_val()); break;};
            case xcom_vtype_int16: { valstr = std::to_string(this->int8_val()); break;};
            case xcom_vtype_uint16: { valstr = std::to_string(this->int16_val()); break;};
            case xcom_vtype_int32: { valstr = std::to_string(this->int32_val()); break;};
            case xcom_vtype_uint32: { valstr = std::to_string(this->uint32_val()); break;};
            case xcom_vtype_int64: { valstr = std::to_string(this->int64_val()); break;};
            case xcom_vtype_uint64: { valstr = std::to_string(this->uint64_val()); break;};
            case xcom_vtype_float: { valstr = std::to_string(this->float_val()); break;};
            case xcom_vtype_double: { valstr = std::to_string(this->double_val()); break;};
            case xcom_vtype_string: { valstr = "\""+this->string_val() + "\""; break;};
            case xcom_vtype_bytes: {
                valstr = this->obj.buf_val->to_var_json();
                break;
            };
            case xcom_vtype_array:
            {
                std::ostringstream ostr;
                ostr << "[";
                auto it = this->obj.array_val->begin();
                auto end = this->obj.array_val->end();
                while(it != end){
                    std::string json = (*it)->to_var_json();
                    ostr << json;
                    it++;
                    if (it != end)
                    {
                        ostr << ",";
                    }
                }
                ostr << "]";
                restr = ostr.str();
                break;
            };
            case xcom_vtype_dict:
            {
                std::ostringstream ostr;
                ostr << "{";
                auto it = this->obj.dict_val->begin();
                auto end = this->obj.dict_val->end();
                while(it != end){
                    std::string json = it->second->to_var_json();
                    ostr << "\""<<it->first << "\":" << json;
                    it++;
                    if (it != end)
                    {
                        ostr << ",";
                    }
                }
                ostr << "}";
                restr = ostr.str();
                break;
            };
            case xcom_vtype_map:
            {
                std::ostringstream ostr;
                ostr << "{";
                auto it = this->obj.map_val->begin();
                auto end = this->obj.map_val->end();
                while(it != end){
                    std::string json = it->second->to_var_json();
                    ostr << "\""<<it->first << "\":" << json;
                    it++;
                    if (it != end)
                    {
                        ostr << ",";
                    }
                }
                ostr << "}";
                restr = ostr.str();
                break;
            };
                
            case xcom_vtype_vptr:
            {
                if (this->obj.vptr_val)
                {
                    std::string str = this->obj.vptr_val->to_var_json();
                    return str.c_str();
                }
                break;
            };
            case xcom_vtype_ref: {
                char buf[64];
                sprintf(buf, "%p", this->obj.ref_val);
                valstr = buf;
                break;
            };
            case xcom_vtype_func: {
                if (this->obj.func_val)
                {
                    restr = this->obj.func_val->to_var_json();
                } else {
                    valstr = "NULL";
                }
                
                break;
            };
        }
        
        if (restr.length() > 0) {
            return restr.c_str();
        }
        std::string str = "{\"" + typestr + "\":" + valstr + "}";
        return str.c_str();
    }
    
    const char *xcom_var::to_json() const
    {
        std::string restr = "";
        std::string typestr = xcom_var_type_string(this->type);
        std::string valstr = "" ;
        switch(this->type)
        {
            case xcom_vtype_null: { valstr = "NULL"; std::string str = "{\"" + typestr + "\":" + valstr + "}"; return str.c_str(); };
            case xcom_vtype_bool: { valstr = this->bool_val() ? "true" : "false"; restr = "{\"" + typestr + "\":" + valstr + "}"; break; };
            case xcom_vtype_int8: { valstr = std::to_string(this->int8_val()); restr = "{\"" + typestr + "\":" + valstr + "}"; break;};
            case xcom_vtype_uint8: { valstr = std::to_string(this->uint8_val()); restr = "{\"" + typestr + "\":" + valstr + "}"; break;};
            case xcom_vtype_int16: { valstr = std::to_string(this->int16_val()); restr = "{\"" + typestr + "\":" + valstr + "}"; break;}
            case xcom_vtype_uint16: { valstr = std::to_string(this->uint16_val()); restr = "{\"" + typestr + "\":" + valstr + "}"; break;}
            case xcom_vtype_int32: { valstr = std::to_string(this->int32_val()); restr = "{\"" + typestr + "\":" + valstr + "}"; break;}
            case xcom_vtype_uint32: { valstr = std::to_string(this->uint32_val()); restr = "{\"" + typestr + "\":" + valstr + "}"; break;}
            case xcom_vtype_int64: { valstr = std::to_string(this->int64_val()); restr = "{\"" + typestr + "\":" + valstr + "}"; break;}
            case xcom_vtype_uint64: { valstr = std::to_string(this->uint64_val()); restr = "{\"" + typestr + "\":" + valstr + "}"; break;}
            case xcom_vtype_float: { valstr = std::to_string(this->float_val()); restr = "{\"" + typestr + "\":" + valstr + "}"; break;}
            case xcom_vtype_double: { valstr = std::to_string(this->double_val()); restr = "{\"" + typestr + "\":" + valstr + "}"; break;}
            case xcom_vtype_string: { valstr = "\""+this->string_val() + "\""; restr = "{\"" + typestr + "\":" + valstr + "}"; break;}
            case xcom_vtype_bytes: {
                valstr = this->obj.buf_val->to_var_json();
                restr = "{\"" + typestr + "\":" + valstr + "}";
                break;
            };
            case xcom_vtype_ref: {
                char buf[64];
                sprintf(buf, "%p", this->obj.ref_val);
                valstr = buf;
                restr = "{\"" + typestr + "\":" + valstr + "}";
                break;
            };
            case xcom_vtype_func: {
                if (this->obj.func_val)
                {
                    valstr = this->obj.func_val->to_json();
                } else {
                    valstr = "NULL";
                }
                restr = "{\"" + typestr + "\":" + valstr + "}";
                break;
            };
            case xcom_vtype_array:
            {
                std::ostringstream ostr;
                ostr << "[";
                auto it = this->obj.array_val->begin();
                auto end = this->obj.array_val->end();
                while(it != end){
                    std::string json = (*it)->to_json();
                    ostr << json;
                    it++;
                    if (it != end)
                    {
                        ostr << ",";
                    }
                }
                ostr << "]";
                restr = ostr.str();
                break;
            };
            case xcom_vtype_dict: {
                std::ostringstream ostr;
                ostr << "{";
                auto it = this->obj.dict_val->begin();
                auto end = this->obj.dict_val->end();
                while(it != end) {
                    xcom_var_ptr ptr = it->second;
                    std::string json = "";
                    if (ptr->type == xcom_vtype_dict || ptr->type == xcom_vtype_map || ptr->type == xcom_vtype_array)
                    {
                        json = it->second->to_json();
                        ostr << "\"" << it->first << "\":" << json ;
                    }
                    else
                    {
                        json = it->second->to_json(it->first.c_str());
                        ostr << json;
                    }
                    
                    
                    it++;
                    if (it != end)
                    {
                        ostr << ",";
                    }
                }
                ostr << "}";
                restr = ostr.str();
                break;
            }
            case xcom_vtype_map: {
                std::ostringstream ostr;
                ostr << "{";
                auto it = this->obj.map_val->begin();
                auto end = this->obj.map_val->end();
                while(it != end) {
                    xcom_var_ptr ptr = it->second;
                    std::string json = "";
                    if (ptr->type == xcom_vtype_dict || ptr->type == xcom_vtype_map || ptr->type == xcom_vtype_array)
                    {
                        json = it->second->to_json();
                        ostr << "\"" << it->first << "\":" << json ;
                    }
                    else
                    {
                        json = it->second->to_json(it->first.c_str());
                        ostr << json;
                    }
                    
                    
                    it++;
                    if (it != end)
                    {
                        ostr << ",";
                    }
                }
                ostr << "}";
                restr = ostr.str();
                break;
            }
            case xcom_vtype_vptr:
            {
                if (this->obj.vptr_val.get())
                {
                    valstr = this->obj.vptr_val->to_json();
                    restr = valstr;
                } else {
                    valstr = "NULL";
                    restr = "{\"" + typestr + "\":" + valstr + "}";
                }
                
                break;
            }
            default:
                return " ";
                
        }
        return restr.c_str();
    }
    
    const char *xcom_var::to_string() const
    {
        std::string res = "";
        switch(this->type)
        {
            case xcom_vtype_bool: res = std::to_string(this->bool_val());break;
            case xcom_vtype_int8: res = std::to_string(this->int8_val());break;
            case xcom_vtype_uint8: res = std::to_string(this->uint8_val());break;
            case xcom_vtype_int16: res = std::to_string(this->int16_val());break;
            case xcom_vtype_uint16: res = std::to_string(this->uint16_val());break;
            case xcom_vtype_int32: res = std::to_string(this->int32_val());break;
            case xcom_vtype_uint32: res = std::to_string(this->uint32_val());break;
            case xcom_vtype_int64: res = std::to_string(this->int64_val());break;
            case xcom_vtype_uint64: res = std::to_string(this->uint64_val());break;
            case xcom_vtype_float: res = std::to_string(this->float_val());break;
            case xcom_vtype_double: res = std::to_string(this->double_val());break;
            case xcom_vtype_string: res = this->string_val();break;
            default:
                break;
        }
        return res.c_str();
    }
    
    const char *xcom_var::to_json(const char *key) const
    {
        if (key == nullptr) {
            return " ";
        }
        
        std::string typestr = std::string(key);
        std::string valstr = "" ;
        switch(this->type)
        {
            case xcom_vtype_null: { valstr = "NULL"; std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); };
            case xcom_vtype_bool: { valstr = this->bool_val() ? "true" : "false"; std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_int8: { valstr = std::to_string(this->int8_val()); std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); };
            case xcom_vtype_uint8: { valstr = std::to_string(this->uint8_val()); std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_int16: { valstr = std::to_string(this->int16_val()); std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_uint16: { valstr = std::to_string(this->uint16_val()); std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_int32: { valstr = std::to_string(this->int32_val()); std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_uint32: { valstr = std::to_string(this->uint32_val()); std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_int64: { valstr = std::to_string(this->int64_val()); std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_uint64: { valstr = std::to_string(this->uint64_val()); std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_float: { valstr = std::to_string(this->float_val()); std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_double: { valstr = std::to_string(this->double_val()); std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_string: { valstr = "\""+this->string_val() + "\""; std::string str = "\"" + typestr + "\":" + valstr; return str.c_str(); }
            case xcom_vtype_bytes: {
                valstr = this->obj.buf_val->to_var_json();
                std::string str = "\"" + typestr + "\":" + valstr; return str.c_str();
                break;
            }
            case xcom_vtype_ref: {
                char buf[64];
                sprintf(buf, "%p", this->obj.ref_val);
                valstr = buf;
                std::string str = "\"" + typestr + "\":" + valstr; return str.c_str();
                break;
            }
            default:
                return " ";
                
        }
        return " ";
    }
    
    //=====================
    //string
    // string
    xcom_var::xcom_var(const std::string &str): xcom_var() {
        this->type = xcom_vtype_string;
        this->obj.string_val = str;
    }
    xcom_var::xcom_var(const char *cstr) : xcom_var() {
        this->type = xcom_vtype_string;
        this->obj.string_val = cstr ? cstr : "";
    }
    
    xcom_var::operator const char *() const {
        return this->type == xcom_vtype_string ? this->obj.string_val.c_str() : "";
    }
    xcom_var::operator std::string () const {
        return this->type == xcom_vtype_string ? this->obj.string_val.c_str() : std::string("");
    }
    
    const char *xcom_var::cstr_val() const  {
        return this->type == xcom_vtype_string ? this->obj.string_val.c_str() : "";
    }
    std::string xcom_var::string_val() const {
        return this->type == xcom_vtype_string ? this->obj.string_val : std::string("");
    }
    
    xcom_var & xcom_var::operator= (const char *cstr) {
        if (this->type == xcom_vtype_vptr) {
            xcom_var_ptr ptr = this->vptr_val();
            *ptr = (cstr == nullptr ? "" : cstr);
        } else {
            this->reset();
            this->type = xcom_vtype_string;
            this->obj.string_val = (cstr == nullptr ? "" : cstr);
        }
        return *this;
    }
    xcom_var & xcom_var::operator= (const std::string &str) {
        if (this->type == xcom_vtype_vptr) {
            xcom_var_ptr ptr = this->vptr_val();
            *ptr = str;
        } else {
            this->reset();
            this->type = xcom_vtype_string;
            this->obj.string_val = str;
        }
        return *this;
    }
    
    bool xcom_var::operator == (const char *cstr) const {
        return this->type != xcom_vtype_string || cstr == nullptr ?  false : this->obj.string_val == std::string(cstr);
    }
    bool xcom_var::operator == (const std::string str) const {
        return this->type != xcom_vtype_string || str.length() == 0 ?  false : this->obj.string_val == str;
    }
    //=====================
    /* array */
    xcom_var_ptr xcom_var::operator[](int32_t index) {
        if (index < 0)
            return nullptr;
        
        init_varray();
        if (index >=0 && index < this->obj.array_val->size()) {
            return at(index);
        }
        if (index == this->obj.array_val->size())
        {
            xcom_var_ptr var_ptr(new xcom_var(0));
            this->obj.array_val->emplace_back(std::move(var_ptr));
            return at(index);
        }
        else {
            printf("Error Index: %d for Array[%d, %d]\n", index, 0, (int)(this->obj.array_val->size()));
            return nullptr;
        }
    }
    
    /* 'index' based array methods */
    void xcom_var::append(const xcom_var &data)
    {
        if (data.type == xcom_vtype_null)
            return;
        
        init_varray();
        if (this->type == xcom_vtype_array)
        {
            xcom_var_ptr var_ptr(new xcom_var(data));
            this->obj.array_val->emplace_back(std::move(var_ptr));
        }
    }
    
    void xcom_var::append(xcom_var &&data)
    {
        if (data.type == xcom_vtype_null)
            return;
        
        init_varray();
        if (this->type == xcom_vtype_array)
        {
            xcom_var_ptr var_ptr(new xcom_var(std::move(data)));
            this->obj.array_val->emplace_back(std::move(var_ptr));
        }
    }
    
    
    bool xcom_var::erase(int32_t index)
    {
        if (this->type == xcom_vtype_array)
        {
            if(index >=0 && index < this->obj.array_val->size())
            {
                this->obj.array_val->erase(this->obj.array_val->begin() + index);
                return true;
            }
        }
        return false;
    }
    
    
    /* 'index' based array methods */
    xcom_var_ptr xcom_var::at(uint32_t index) {
        
        if(index >=0 && index < this->obj.array_val->size())
        {
            return (*this->obj.array_val)[index];
        }
        
        return nullptr;
    }
    
    void xcom_var::init_varray()
    {
        if (this->type != xcom_vtype_array)
        {
            this->reset();
            this->type = xcom_vtype_array;
            this->obj.array_val = new xcom_var_array;
        }
    }
    //=====================
    /* dict */
    
    void xcom_var::insert(const char *key, const xcom_var &value, bool is_dic_insert)
    {
        if (!key || !*key)
            return;
        
        if (this->type == xcom_vtype_dict && is_dic_insert) {
            *(*this)[key] = value;
        } else {
            init_vmap();
            this->put(key, value);
        }
        
    }
    xcom_var_ptr xcom_var::operator[](const char *key) {
        if (!key || !*key)
            return nullptr;
        
        if (this->type == xcom_vtype_dict) {
            if (!this->contains(key))
            {
                this->put(key);
            }
            
            xcom_var_ptr ptr = get(key);
            printf("get ptr : %p : %s\n", ptr.get(), ptr->to_var_json());
            return ptr;
        }
        else if (this->type == xcom_vtype_map)
        {
            if (this->contains(key))
            {
                xcom_var_ptr ptr = get(key);
                return ptr;
            }
            return nullptr;
        }
        else
        {
            if (this->type != xcom_vtype_dict) {
                init_vdict();
            }
            if (!this->contains(key))
            {
                this->put(key);
            }
            
            xcom_var_ptr ptr = get(key);
            printf("get ptr : %p : %s\n", ptr.get(), ptr->to_var_json());
            return ptr;
        }
    }
    
    bool xcom_var::contains(const char *key)
    {
        if (this->type == xcom_vtype_dict)
        {
            if (this->obj.dict_val) {
                for (auto it = this->obj.dict_val->begin(); it != this->obj.dict_val->end(); it++) {
                    if (it->first == key ) {
                        return true;
                    }
                }
            }
            
        }
        else if (this->type == xcom_vtype_map)
        {
            if (this->obj.map_val) {
                auto it = this->obj.map_val->find(key);
                if (it != this->obj.map_val->end()) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool xcom_var::erase(const char *key) {
        if (this->type == xcom_vtype_dict)
        {
            if(this->obj.dict_val) {
                for (auto it = this->obj.dict_val->begin(); it != this->obj.dict_val->end(); it++) {
                    if (it->first == key ) {
                        this->obj.dict_val->erase(it);
                        return true;
                    }
                }
            }
        }
        else if (this->type == xcom_vtype_map) {
            if(this->obj.map_val) {
                auto it = this->obj.map_val->find(key);
                if (it != this->obj.map_val->end())
                {
                    it->second.reset();
                    this->obj.map_val->erase(it);
                    return true;
                }
            }
        }
        return false;
    }
    
    void xcom_var::init_vdict()
    {
        if (this->type != xcom_vtype_dict)
        {
            this->reset();
            this->type = xcom_vtype_dict;
            this->obj.dict_val = new xcom_var_dict;
        }
    }
    
    void xcom_var::init_vmap()
    {
        if (this->type != xcom_vtype_map)
        {
            this->reset();
            this->type = xcom_vtype_map;
            this->obj.map_val = new xcom_var_map;
        }
    }
    
    /* 'key-value' dictionary methods */
    void xcom_var::put(const char *key) {
        
        xcom_var_ptr cpy(new xcom_var(0));
        printf("crate ptr : %p\n", cpy.get());
        this->obj.dict_val->push_back(std::make_pair(key, cpy));
    }
    
    void xcom_var::put(const char *key, const xcom_var &value)
    {
        xcom_var_ptr cpy(new xcom_var(value));
        printf("crate ptr : %p  , %s\n", cpy.get(), cpy->to_var_json());
        this->obj.map_val->insert(std::make_pair(key, cpy));
    }
    
    xcom_var_ptr xcom_var::get(const char *key) {
        if (this->type == xcom_vtype_dict) {
            auto it = this->obj.dict_val->begin();
            while (it != this->obj.dict_val->end()) {
                if (it->first == key) {
                    return it->second;
                }
                it++;
            }
        }
        else if (this->type == xcom_vtype_map) {
            auto it = this->obj.map_val->find(key);
            if (it != this->obj.map_val->end())
            {
                return it->second;
            }
        }
        
        return nullptr;
    }
    //=====================
    /* buffer */
    void xcom_var::set_buffer(const void *data, uint32_t len) {
        if (data != nullptr && len > 0) {
            this->reset();
            this->type = xcom_vtype_bytes;
            this->obj.buf_val = new xcom_var_buf(data, len);
        }
    }
    //================
    
    bool xcom_var::is_zero() const
    {
        switch (this->type) {
            case xcom_vtype_null: return true;
            case xcom_vtype_bool: return !this->bool_val();
            case xcom_vtype_int8: return this->int8_val() == 0;
            case xcom_vtype_uint8: return this->uint8_val() == 0;
            case xcom_vtype_int16: return this->int16_val() == 0;
            case xcom_vtype_uint16: return this->uint16_val() == 0;
            case xcom_vtype_int32: return this->int32_val() == 0;
            case xcom_vtype_uint32: return this->uint32_val() == 0;
            case xcom_vtype_int64: return this->int64_val() == 0;
            case xcom_vtype_uint64: return this->uint64_val() == 0;
            case xcom_vtype_float: return this->float_val() == 0;
            case xcom_vtype_double: return this->double_val() == 0;
            default:
                return false;
                break;
        }
        return true;
    }
    bool xcom_var::empty() const
    {
        if (this->type == xcom_vtype_array )
        {
            return this->obj.array_val->empty();
        }
        else if (this->type == xcom_vtype_dict)
        {
            return this->obj.dict_val->empty();
        }
        else if (this->type == xcom_vtype_vptr) {
            if (this->obj.vptr_val) {
                return this->obj.vptr_val->empty();
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    uint32_t xcom_var::size()
    {
        if (this->type == xcom_vtype_array )
        {
            return (uint32_t)this->obj.array_val->size();
        }
        else if (this->type == xcom_vtype_dict)
        {
            return (uint32_t)this->obj.dict_val->size();
        }
        else if (this->type == xcom_vtype_vptr) {
            if (this->obj.vptr_val) {
                return this->obj.vptr_val->size();
            }
            return 0;
        }
        else
        {
            return 1;
        }
    }
    
    //===================
    // 操作符重载
    
    xcom_var operator+(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        if (a.type > xcom_vtype_string || b.type > xcom_vtype_string)
        {
            std::string astr = a.to_var_json();
            std::string bstr = b.to_var_json();
            std::string funcname = __FUNCTION__;
            std::string error =  " logic error :"  + funcname + "(" + astr + "," + bstr + ")";
            throw std::logic_error(error);
        }
        
        if (a.type == xcom_vtype_null) {return xcom_var(b);}
        if (b.type == xcom_vtype_null) {return xcom_var(a);}
        
        if (a.type < xcom_vtype_string && b.type < xcom_vtype_string) {
            xcom_num_base_opera(a, b, xcom_add);
        }
        else {
            // string 相加
            if (a.type == xcom_vtype_string) {
                std::string bstr = b.to_string();
                return xcom_var(a.string_val() + bstr);
            }
            else if (b.type == xcom_vtype_string) {
                return b + a;
            }
        }
        
        // 实际不可达
        return a;
    }
    
    xcom_var operator-(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        if (a.type >= xcom_vtype_string || b.type >= xcom_vtype_string)
        {
            std::string astr = a.to_var_json();
            std::string bstr = b.to_var_json();
            std::string funcname = __FUNCTION__;
            std::string error =  " logic error :"  + funcname + "(" + astr + "," + bstr + ")";
            throw std::logic_error(error);
        }
        
        if (a.type == xcom_vtype_null) {
            return -b;
        }
        if (b.type == xcom_vtype_null) {return xcom_var(a);}
        
        if (a.type < xcom_vtype_string && b.type < xcom_vtype_string) {
            xcom_num_base_opera(a, b, xcom_dec);
        }
        
        // 实际不可达
        return a;
    }
    
    xcom_var operator*(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        if (a.type > xcom_vtype_string || b.type > xcom_vtype_string)
        {
            std::string astr = a.to_var_json();
            std::string bstr = b.to_var_json();
            std::string funcname = __FUNCTION__;
            std::string error =  " logic error :"  + funcname + "(" + astr + "," + bstr + ")";
            throw std::logic_error(error);
        }
        
        if (a.type == xcom_vtype_null) {return xcom_var();}
        if (b.type == xcom_vtype_null) {return xcom_var();}
        
        if (a.type < xcom_vtype_string && b.type < xcom_vtype_string) {
            xcom_num_base_opera(a, b, xcom_mul);
        }
        // 实际不可达
        return a;
    }
    
    xcom_var operator/(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        if (a.type >= xcom_vtype_string || b.type >= xcom_vtype_string)
        {
            std::string astr = a.to_var_json();
            std::string bstr = b.to_var_json();
            std::string funcname = __FUNCTION__;
            std::string error =  " logic error :"  + funcname + "(" + astr + "," + bstr + ")";
            throw std::logic_error(error);
        }
        
        
        if (b.type == xcom_vtype_null) {
            return xcom_var(a);
        }
        
        if (b.is_zero()){
            std::string astr = a.to_var_json();
            std::string bstr = b.to_var_json();
            std::string funcname = __FUNCTION__;
            std::string error =  " logic error :"  + funcname + "(" + astr + "," + bstr + ")" + "divisor is zero";
            throw std::logic_error(error);
        }
        
        
        if (a.type == xcom_vtype_null) {
            return xcom_var(0);
        }
        if (a.type < xcom_vtype_string && b.type < xcom_vtype_string) {
            xcom_num_base_opera(a, b, xcom_div);
        }
        
        // 实际不可达
        return a;
    }
    xcom_var operator%(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        if (a.type >= xcom_vtype_float || b.type >= xcom_vtype_float)
        {
            std::string astr = a.to_var_json();
            std::string bstr = b.to_var_json();
            std::string funcname = __FUNCTION__;
            std::string error =  " logic error :"  + funcname + "(" + astr + "," + bstr + ") has float or double";
            throw std::logic_error(error);
        }
        
        
        if (b.type == xcom_vtype_null) {
            return xcom_var(a);
        }
        
        if (b.is_zero()){
            std::string astr = a.to_var_json();
            std::string bstr = b.to_var_json();
            std::string funcname = __FUNCTION__;
            std::string error =  " logic error :"  + funcname + "(" + astr + "," + bstr + ")" + "remainder is zero";
            throw std::logic_error(error);
        }
        
        
        if (a.type == xcom_vtype_null) {
            return xcom_var(0);
        }
        if (a.type < xcom_vtype_float && b.type < xcom_vtype_float) {
            xcom_num_mode_opera(a, b);
        }
        
        // 实际不可达
        return a;
    }
    
    bool operator !=(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        xcom_compare(a, b, xcom_not_equalto);
        // 实际不可达
        return false;
    }
    bool operator ==(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        xcom_compare(a, b, xcom_equalto);
        // 实际不可达
        return false;
    }
    bool operator < (const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        xcom_compare(a, b, xcom_less_than);
        // 实际不可达
        return false;
    }
     bool operator > (const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        xcom_compare(a, b, xcom_greater_than);
        // 实际不可达
        return false;
    }
     bool operator <=(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        xcom_compare(a, b, xcom_less_than_equalto);
        // 实际不可达
        return false;
    }
    bool operator >=(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        xcom_compare(a, b, xcom_greater_than_equalto);
        // 实际不可达
        return false;
    }
    
    xcom_var operator||(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        if (a.type >= xcom_vtype_string || b.type >= xcom_vtype_string || a.type == xcom_vtype_null || b.type == xcom_vtype_null)
        {
            std::string astr = a.to_var_json();
            std::string bstr = b.to_var_json();
            std::string funcname = __FUNCTION__;
            std::string error =  " logic error :"  + funcname + "(" + astr + "," + bstr + ")";
            throw std::logic_error(error);
        }
        else {
            xcom_logic_opera(a, b, xcom_logic_or);
        }
        // 实际不可达
        return xcom_var(false);
    }
    xcom_var operator&&(const xcom_var& a, const xcom_var& b) throw(std::logic_error)
    {
        if (a.type >= xcom_vtype_string || b.type >= xcom_vtype_string || a.type == xcom_vtype_null || b.type == xcom_vtype_null)
        {
            std::string astr = a.to_var_json();
            std::string bstr = b.to_var_json();
            std::string funcname = __FUNCTION__;
            std::string error =  " logic error :"  + funcname + "(" + astr + "," + bstr + ")";
            throw std::logic_error(error);
        }
        else {
            xcom_logic_opera(a, b, xcom_logic_and);
        }
        // 实际不可达
        return xcom_var(false);
    }
    xcom_var operator!(const xcom_var& a) throw(std::logic_error)
    {
        switch (a.type) {
            case xcom_vtype_bool:  return xcom_var(!a.bool_val());
            case xcom_vtype_int8:  return xcom_var(!a.int8_val());
            case xcom_vtype_uint8: return xcom_var(!a.uint8_val());
            case xcom_vtype_int16: return xcom_var(!a.int16_val());
            case xcom_vtype_uint16:return xcom_var(!a.uint16_val());
            case xcom_vtype_int32: return xcom_var(!a.int32_val());
            case xcom_vtype_uint32:return xcom_var(!a.uint32_val());
            case xcom_vtype_int64: return xcom_var(!a.int64_val());
            case xcom_vtype_uint64:return xcom_var(!a.uint64_val());
            case xcom_vtype_float: return xcom_var(!a.float_val());
            case xcom_vtype_double:return xcom_var(!a.double_val());
            break;
            default:
            std::string str = a.to_var_json();
            std::string funcname = __FUNCTION__;
            std::string error =  " logic error :"  + funcname + "(" + str + ")";
            throw std::logic_error(error);
            break;
        }
    }
    
    xcom_var xcom_var::operator +() const throw(std::logic_error)
    {
        switch (this->type) {
            case xcom_vtype_null:
            case xcom_vtype_bool:  return xcom_var(+this->bool_val());
            case xcom_vtype_int8:  return xcom_var(+this->int8_val());
            case xcom_vtype_uint8: return xcom_var(+this->uint8_val());
            case xcom_vtype_int16: return xcom_var(+this->int16_val());
            case xcom_vtype_uint16:return xcom_var(+this->uint16_val());
            case xcom_vtype_int32: return xcom_var(+this->int32_val());
            case xcom_vtype_uint32:return xcom_var(+this->uint32_val());
            case xcom_vtype_int64: return xcom_var(+this->int64_val());
            case xcom_vtype_uint64:return xcom_var(+this->uint64_val());
            case xcom_vtype_float: return xcom_var(+this->float_val());
            case xcom_vtype_double:return xcom_var(+this->double_val());
                break;
            default:
                std::string str = this->to_var_json();
                std::string funcname = __FUNCTION__;
                std::string error =  " logic error :"  + funcname + "(" + str + ")";
                throw std::logic_error(error);
                break;
        }
    }
    xcom_var xcom_var::operator -() const throw(std::logic_error)
    {
        switch (this->type) {
            case xcom_vtype_null:
            case xcom_vtype_bool:  return xcom_var(0-this->bool_val());
            case xcom_vtype_int8:  return xcom_var(-this->int8_val());
            case xcom_vtype_uint8: return xcom_var(-this->uint8_val());
            case xcom_vtype_int16: return xcom_var(-this->int16_val());
            case xcom_vtype_uint16:return xcom_var(-this->uint16_val());
            case xcom_vtype_int32: return xcom_var(-this->int32_val());
            case xcom_vtype_uint32:return xcom_var(-this->uint32_val());
            case xcom_vtype_int64: return xcom_var(-this->int64_val());
            case xcom_vtype_uint64:return xcom_var(-this->uint64_val());
            case xcom_vtype_float: return xcom_var(-this->float_val());
            case xcom_vtype_double:return xcom_var(-this->double_val());
                break;
            default:
                std::string str = this->to_var_json();
                std::string funcname = __FUNCTION__;
                std::string error =  " logic error :"  + funcname + "(" + str + ") just for number";
                throw std::logic_error(error);
                break;
        }
    }
    
    
    std::ostream & operator <<(std::ostream &os, const xcom_var &a )
    {
        os<< a.to_json();
        return os;
    }
    
#ifdef __cplusplus
    //    }
#endif
}

