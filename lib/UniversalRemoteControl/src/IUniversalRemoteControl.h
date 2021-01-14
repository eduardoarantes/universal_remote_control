/*
    IRemoteControl - record and sends combination of codes to automate devices
    Created by Eduardo Rodrigues, January 10, 2021.

*/
#include <IonDB.h>

#ifndef IRemoteControl
#define IRemoteControl
 
class RemoteControl
{
    public:
        RemoteControl();
        // return the action name if the code exists
        String hasCode(unsigned long);
        void addCode(unsigned long, String);
    private:
        Dictionary<unsigned long, String> *_codes;
};

class UniversalRemoteControl
{
  public:
    UniversalRemoteControl();
    RemoteControl activateSenderRemote(String);
    RemoteControl getSenderRemote(String);
    
  private:
    RemoteControl _activeSenderRemote ;

    // Dictionary<String, unsigned long> *activeCommands = new SkipList<String, unsigned long>(-1, key_type_numeric_signed, sizeof(int), sizeof(int), 7);

};


#endif

