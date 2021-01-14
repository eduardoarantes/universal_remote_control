#include <IUniversalRemoteControl.h>

RemoteControl::RemoteControl(){
    _codes = new SkipList<long, String>(-1, key_type_numeric_signed, sizeof(long), 20, 7);
}
String RemoteControl:: hasCode( long code){
    return _codes->get(code);
}
void RemoteControl:: addCode( long code, long action){
    _codes->insert(code, action);
}

UniversalRemoteControl::UniversalRemoteControl(){
    
}
RemoteControl UniversalRemoteControl:: activateSenderRemote(String remoteName){
    return RemoteControl();
}
RemoteControl UniversalRemoteControl:: getSenderRemote(String remoteName){
    return RemoteControl();
}
