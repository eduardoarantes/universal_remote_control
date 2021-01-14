#include <IUniversalRemoteControl.h>
#include <IonDB.h>

RemoteControl::RemoteControl(){
    this->_codes = SkipList<unsigned long, String>(-1, key_type_numeric_signed, sizeof(long), 20, 7);
}
String RemoteControl:: hasCode(unsigned long code){
    return this->_codes.get(code);
}
void RemoteControl:: addCode(unsigned long code, String action){
    this->_codes.insert(code, action);
}


UniversalRemoteControl::UniversalRemoteControl(){
    
}
RemoteControl UniversalRemoteControl:: activateSenderRemote(String remoteName){
    return RemoteControl();
}
RemoteControl UniversalRemoteControl:: getSenderRemote(String remoteName){

}
