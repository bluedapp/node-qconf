#include <nan.h>
#include <qconf.h>

void QConfVersion(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    const char *ver = qconf_version();
    info.GetReturnValue().Set(Nan::New(ver).ToLocalChecked());
}

void QConfGetConf(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    const char *path = NULL;
    const char *idc = NULL;
    char value[QCONF_CONF_BUF_MAX_LEN];
    int ret;

    if (info.Length() < 1) {
        Nan::ThrowTypeError("Wrong number of arguments: at least 1");
        return;
    }

    Nan::Utf8String s0(info[0]);
    path = *s0;

    if (info.Length() >= 2) {
        Nan::Utf8String s1(info[1]);
        idc = *s1;
    }

    ret = qconf_aget_conf(path, value, sizeof(value), idc);
    if (ret != QCONF_OK) {
        info.GetReturnValue().Set(Nan::Null());
        return;
    }

    info.GetReturnValue().Set(Nan::New(value).ToLocalChecked());
}

void QConfGetBatchKeys(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    const char *path = NULL;
    const char *idc = NULL;
    string_vector_t keys;
    int ret;
    int i;

    if (info.Length() < 1) {
        Nan::ThrowTypeError("Wrong number of arguments: at least 1");
        return;
    }

    Nan::Utf8String s0(info[0]);
    path = *s0;

    if (info.Length() >= 2) {
        Nan::Utf8String s1(info[1]);
        idc = *s1;
    }

    init_string_vector(&keys);
    ret = qconf_aget_batch_keys(path, &keys, idc);
    if (ret != QCONF_OK) {
        info.GetReturnValue().Set(Nan::Null());
        return;
    }

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(keys.count);
    for (i = 0; i < keys.count; i++) {
        arr->Set(i, Nan::New(keys.data[i]).ToLocalChecked());
    }

    destroy_string_vector(&keys);
    
    info.GetReturnValue().Set(arr);
}

void QConfGetBatchConf(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    const char *path = NULL;
    const char *idc = NULL;
    qconf_batch_nodes nodes;
    int ret;
    int i;

    if (info.Length() < 1) {
        Nan::ThrowTypeError("Wrong number of arguments: at least 1");
        return;
    }

    Nan::Utf8String s0(info[0]);
    path = *s0;

    if (info.Length() >= 2) {
        Nan::Utf8String s1(info[1]);
        idc = *s1;
    }

    init_qconf_batch_nodes(&nodes);
    ret = qconf_aget_batch_conf(path, &nodes, idc);
    if (ret != QCONF_OK) {
        info.GetReturnValue().Set(Nan::Null());
        return;
    }

    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    for (i = 0; i < nodes.count; i++) {
        if (strcmp(nodes.nodes[i].value, "") == 0) {
            obj->Set(Nan::New(nodes.nodes[i].key).ToLocalChecked(),
                     Nan::EmptyString());
        } else {
            obj->Set(Nan::New(nodes.nodes[i].key).ToLocalChecked(),
                     Nan::New(nodes.nodes[i].value).ToLocalChecked());
        }
    }

    destroy_qconf_batch_nodes(&nodes);
    
    info.GetReturnValue().Set(obj);
}

void QConfGetAllHost(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    const char *path = NULL;
    const char *idc = NULL;
    string_vector_t hosts;
    int ret;
    int i;

    if (info.Length() < 1) {
        Nan::ThrowTypeError("Wrong number of arguments: at least 1");
        return;
    }

    Nan::Utf8String s0(info[0]);
    path = *s0;

    if (info.Length() >= 2) {
        Nan::Utf8String s1(info[1]);
        idc = *s1;
    }

    init_string_vector(&hosts);
    ret = qconf_aget_allhost(path, &hosts, idc);
    if (ret != QCONF_OK) {
        info.GetReturnValue().Set(Nan::Null());
        return;
    }

    v8::Local<v8::Array> arr = Nan::New<v8::Array>(hosts.count);
    for (i = 0; i < hosts.count; i++) {
        arr->Set(i, Nan::New(hosts.data[i]).ToLocalChecked());
    }

    destroy_string_vector(&hosts);
    
    info.GetReturnValue().Set(arr);
}

void QConfGetHost(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    const char *path = NULL;
    const char *idc = NULL;
    char host[QCONF_HOST_BUF_MAX_LEN];
    int ret;

    if (info.Length() < 1) {
        Nan::ThrowTypeError("Wrong number of arguments: at least 1");
        return;
    }

    Nan::Utf8String s0(info[0]);
    path = *s0;

    if (info.Length() >= 2) {
        Nan::Utf8String s1(info[1]);
        idc = *s1;
    }

    ret = qconf_aget_host(path, host, sizeof(host), idc);
    if (ret != QCONF_OK) {
        info.GetReturnValue().Set(Nan::Null());
        return;
    }

    info.GetReturnValue().Set(Nan::New(host).ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports) {
    int ret = qconf_init();
    if (ret != QCONF_OK) {
        char errmsg[32];
        sprintf(errmsg, "QConf init failed: %d", ret);
        Nan::ThrowError(Nan::Error(errmsg));
    }

    exports->Set(Nan::New("version").ToLocalChecked(),
             Nan::New<v8::FunctionTemplate>(QConfVersion)->GetFunction());
    exports->Set(Nan::New("getConf").ToLocalChecked(),
             Nan::New<v8::FunctionTemplate>(QConfGetConf)->GetFunction());
    exports->Set(Nan::New("getBatchKeys").ToLocalChecked(),
             Nan::New<v8::FunctionTemplate>(QConfGetBatchKeys)->GetFunction());
    exports->Set(Nan::New("getBatchConf").ToLocalChecked(),
             Nan::New<v8::FunctionTemplate>(QConfGetBatchConf)->GetFunction());
    exports->Set(Nan::New("getAllHost").ToLocalChecked(),
             Nan::New<v8::FunctionTemplate>(QConfGetAllHost)->GetFunction());
    exports->Set(Nan::New("getHost").ToLocalChecked(),
             Nan::New<v8::FunctionTemplate>(QConfGetHost)->GetFunction());
}

NODE_MODULE(qconf, Init)