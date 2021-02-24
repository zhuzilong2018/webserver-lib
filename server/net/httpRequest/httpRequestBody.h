#pragma once
#include "../../exception/httpException.h"

namespace net{
    enum class ContentType{
        application_x_www_form_urlencoded
    };
    class HttpRequestBody{
    public:
        using ParameterMap = std::unordered_map<std::string, std::string>;
        const std::string getParameter(const std::string key){
            if(parameterMap.count(key) > 0){
                return parameterMap[key];
            }
            return "";
        }
        void setContentType(const std::string& type){
            if(type == "application/x-www-form-urlencoded"){
                this->contentType = ContentType::application_x_www_form_urlencoded;
            }
            else{
                throw exception::HttpException("未知Content-Type类型");
            }
            
        }
        const ContentType getContentType()const{
            return this->contentType;
        }
        void setParameter(std::string key, std::string value){
            this->parameterMap[key] = value;
        }
        const std::string getParametersAsString()const{
            std::string result("{<br/>");
            for(auto iter = this->parameterMap.begin(); iter != this->parameterMap.end();){
                result += iter->first;
                result += ':';
                result += iter->second;
                iter++;
                if(iter != this->parameterMap.end()) result += ";<br/>";
            }
            result += "<br/>}<br/>";
            return result;
        }
        void append(std::string&& data){
            _data.append(std::move(data));
        }
        void append(const std::string& data){
            _data.append(data);
        }
        const std::string getAsString()const{
            return _data;
        }
        ParameterMap parameterMap;
        std::string _data;
    private:
        ContentType contentType;
    };
}