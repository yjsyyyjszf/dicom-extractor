#include "../source/logxx/logxx.h"
#include "config.h"
#include "../source/dicom/dicom.h"

static logxx::Log cLog("Testing");

template<class T>
bool Compare(const std::string& label, const T& etalon, const T& testing){
        S_LOG("CompareStr");
        if (etalon == testing)
                return true;
        else {
                log(logxx::info) << "Faild comaring " << label << ": should be {" << etalon << "}, got {" << testing << "}" << logxx::endl;
                return false;
        }
}

bool TestFile(const std::string& filename, const std::string &surname, const std::string &pet, int id, const std::string& date){
        S_LOG("TestFile");
        Dicom dicomFile(filename);
        if (dicomFile.Parse()){
                if (Compare("surname", surname, dicomFile.GetName()) &&
                        Compare("pet", pet, dicomFile.GetPet()) &&
                        Compare("id", id, dicomFile.GetId()) &&
                        Compare("date", date, dicomFile.GetDate()))
                        return true;
                else {
                        log(logxx::error) << "Test failed for {" << filename << "}" << logxx::endl;
                        return false;
                }
        } else {
                log(logxx::error) << "Can't parse {" << filename << "}" << logxx::endl;
                return false;
        }
}

int main(){
        logxx::GlobalLogLevel(logxx::debug);
	S_LOG("main");
        return (
                TestFile(DATA_DIR "1_16_37_40_1-cut.dcm", "иващенко", "тима", 8010, "20120101") &&
                TestFile(DATA_DIR "10_21_16_57_1-cut.dcm", "егорова", "альгамбра", 31559, "19980930") &&
                TestFile(DATA_DIR "28_10_14_45_1-cut.dcm", "Герасимчук", "Шейла", 39020, "20130528") &&
                TestFile(DATA_DIR "31_16_16_31_1-cut.dcm", "искандерова", "матильда", 38742, "20130502")
                ) ? 0 : 1;
        
}