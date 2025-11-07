#include <iostream>

#include "abstractDataTypes/SubsetUnion.hpp"
#include "ClinicModel/ClinicModelFactory.hpp"
#include "ClinicModel/ClinicModelPackage.hpp"

#include "ClinicModel/AdministrationFacility.hpp"
#include "ClinicModel/Clinic.hpp"
#include "ClinicModel/Facility.hpp"
#include "ClinicModel/GeneralFacility.hpp"
#include "ClinicModel/SpecializedFacility.hpp"
#include "ClinicModel/Staff.hpp"

//Includes from main behavior mainProgram
#include "ClinicModel/Facility.hpp"
#include "ClinicModel/Staff.hpp"
#include "ClinicModel/GeneralFacility.hpp"
#include "ClinicModel/SpecializedFacility.hpp"
#include "ClinicModel/Clinic.hpp"
#include "ClinicModel/AdministrationFacility.hpp"
#include <chrono>
#include <iostream>

#include <string>
#include <fstream>

bool isFileEmpty(const std::string& filename)

{
    
	std::ifstream file(filename);
    
	return file.peek() == std::ifstream::traits_type::eof();

}

using namespace ClinicModel;

int main ()
{
	//Create Model Factory and Package
	std::shared_ptr<ClinicModelFactory> factory = ClinicModelFactory::eInstance();
	std::shared_ptr<ClinicModelPackage> package = ClinicModelPackage::eInstance();

	int Num_Elements = 0;
int runNumber = 0;
// Reading Num_Elements and runNumber 
std::ifstream configFile("C:/MDE4CPP/MDE4CPP/application/bin/umlinput.txt");
if (!configFile.is_open())
{
    std::cerr << "Error opening config.txt" << std::endl;
    return 1;
}
configFile >> Num_Elements >> runNumber;
configFile.close();
if (Num_Elements <= 0 || runNumber <= 0) 
{
     std::cerr << "Invalid values" << std::endl;
     return 1;
}

std::ofstream csvFile("C:/MDE4CPP/MDE4CPP/application/runtimeUML/ClinicModel_times.csv", std::ios::app);
if (!csvFile) 
{
    std::cerr << "Error opening ClinicModel_times.csv" << std::endl;
    return 1;
}
if (isFileEmpty("C:/MDE4CPP/MDE4CPP/application/runtimeUML/ClinicModel_times.csv")) 
{
        csvFile << "RUN,Num_Elements,Time1,Time2,Time3,Time4,Time5,Time6,Time7, DeletionTime\n";
}

long time1, time2, time3, time4, time5, time6, time7, deletionTime;
std::chrono::time_point<std::chrono::high_resolution_clock>start,end,startTimedeletion,endDeletion,finalend;

int iterationNum=10;
{		//Create Model Factory and Package
	std::shared_ptr<ClinicModelFactory> factory = ClinicModelFactory::eInstance();
	std::shared_ptr<ClinicModelPackage> package = ClinicModelPackage::eInstance();
	
	for(int j=0;j<iterationNum;j++)
	{	
		{
			std::shared_ptr<Clinic> clinic = factory->createClinic();
			std::string clinicName = "Sample Clinic"; // Example clinic 
			clinic->setClinicName(clinicName);
			
			const int numStaffTypes = 6; // Number of staff types
			// Staff types and their respective attributes
			std::string staffRoles[numStaffTypes] = {"Doctor", "Nurse", "Admin", "Doctor", "Nurse", "Admin"};
			std::string doctorSpecialties[numStaffTypes] = {"Cardiology", "", "", "Neurology", "", ""}; // Specialties for doctors
			std::string nurseWards[numStaffTypes] = {"", "ICU", "", "", "Pediatrics", ""}; // Wards for nurses
			std::string adminDepartments[numStaffTypes] = {"", "", "HR", "", "", "Finance"}; // Departments for admins
			
			// Adding staff to the clinic- first operation
			start = std::chrono::high_resolution_clock::now();						
			for (int i = 0; i < Num_Elements; i++) 
			{
				// Generating staff name and role dynamically
				std::string staffName = "Staff_" + std::to_string(i + 1);
				std::string staffRole = staffRoles[i % numStaffTypes];  // Cycle through roles

				// Creating Staff				
				std::shared_ptr<Staff> staff = factory->createStaff_as_staffs_in_Clinic(clinic);
				staff->setName(staffName);
				staff->setRole(staffRole);
				
				// Set additional properties based on role
				if(staffRole=="Doctor")
				{
					staff->setSpecialty(doctorSpecialties[i % numStaffTypes]);
				} 
				else if (staffRole == "Nurse") 
				{
						staff->setWard(nurseWards[i % numStaffTypes]);
				} 
				else if (staffRole == "Admin") 
				{
						staff->setDepartment(adminDepartments[i % numStaffTypes]);
				}
			}
			end = std::chrono::high_resolution_clock::now();
			time1=std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			//std::cout << "Time taken to add all staff: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "ms" << std::endl;
					
			const int numSpecializedFacilities = 5;
			std::string specializedFacilityAddresses[numSpecializedFacilities] = {"SpecFacility Address 1", "SpecFacility Address 2", "SpecFacility Address 3", "SpecFacility Address 4", "SpecFacility Address 5"};
			std::string specializedFacilitySpecializations[numSpecializedFacilities] = {"Cardiology", "Neurology", "Oncology", "Pediatrics", "Radiology"};

			const int numGeneralFacilities = 5;
			std::string generalFacilityAddresses[numGeneralFacilities] = {"GenFacility Address 1", "GenFacility Address 2", "GenFacility Address 3", "GenFacility Address 4", "GenFacility Address 5"};

			const int numAdminFacilities = 5;
			std::string adminFacilityAddresses[numAdminFacilities] = {"AdminFacility Address 1", "AdminFacility Address 2", "AdminFacility Address 3", "AdminFacility Address 4", "AdminFacility Address 5"};
			std::string adminFacilityDepartments[numAdminFacilities] = {"HR", "Finance", "IT", "Marketing", "Admissions"};

			// Start of dynamic facility addition
			// Add Specialized Facilities - 2nd operation
			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < Num_Elements; i++) 
			{	
				std::shared_ptr<SpecializedFacility> sfacility = factory->createSpecializedFacility_as_specialfacilities_in_Clinic(clinic);
				sfacility->setAddress(specializedFacilityAddresses[i % numSpecializedFacilities]);
				sfacility->setSpecialization(specializedFacilitySpecializations[i % numSpecializedFacilities]);
						
			}
			end = std::chrono::high_resolution_clock::now();
			time2= std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
				//std::cout << "Time taken to add all specialized facilities: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "ms" << std::endl;

				// Add General Facilities- 3rd operation
			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < Num_Elements; i++) 
			{
				std::shared_ptr<GeneralFacility> gfacility = factory->createGeneralFacility_as_generalfacilities_in_Clinic(clinic);
				gfacility->setAddress(generalFacilityAddresses[i % numGeneralFacilities]);
			}
			end = std::chrono::high_resolution_clock::now();
			time3=std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
				
				//std::cout << "Time taken to add all generalfacility: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "ms" << std::endl;
					
				// Add Admin Facilities- 4th operation
			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < Num_Elements; i++) 
			{
				std::shared_ptr<AdministrationFacility> adfacility = factory->createAdministrationFacility_as_employAdmins_in_Clinic(clinic);
				adfacility->setAddress(adminFacilityAddresses[i % numAdminFacilities]);
				adfacility->setAdminDept(adminFacilityDepartments[i % numAdminFacilities]);	
			}
			end = std::chrono::high_resolution_clock::now();
			time4= std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
				
				// changing nurse facility - 5th operation
			const int Num_Nurses = Num_Elements; 
			std::string nurseRolesNew="Nurse";
				// Change nurse facilities
			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < Num_Nurses; i++) 
			{	
				std::shared_ptr<Staff> nurse = nullptr;
				std::shared_ptr<Bag<Staff>> staffs = clinic->getStaffs();
				std::string nurseNamesNew = "Nurse_" + std::to_string(i + 1);
				std::string nurseNewWardsNew= (i % 3 == 0) ? "ICU" : (i % 3 == 1) ? "Pediatrics" : "Emergency";
				std::string newNurseAddressesNew= "New Address " + std::to_string(i + 1);
					
				// Find the nurse by name, role, and ward
				Bag<Staff>::const_iterator endit=staffs->end();
				for (Bag<Staff>::const_iterator it = staffs->begin(); it != endit; it++) 
				{
					std::string itName = (*it)->getName();
					std::string itRole = (*it)->getRole();
					std::string itWard = (*it)->getWard();
											
					if (itName == nurseNamesNew  && itRole == nurseRolesNew && itWard == nurseNewWardsNew) 
					{
						nurse = (*it);
						break; // Exit loop once the nurse is found
					}
				}

				if (nurse != nullptr) 
				{
						clinic->changeNurseFacility(nurse, newNurseAddressesNew);
						// std::cout << "Nurse " << nurseNames[i] << " assigned to new facility: " << newNurseAddresses[i] << std::endl;
				} 
			}
			end = std::chrono::high_resolution_clock::now();
			time5=std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
				
			//changing doctor facilities- 6th operation
			const int numDoctors = Num_Elements;
			std::string doctorRolesNew="Doctor";
			// Change doctor facilities
			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < numDoctors; i++) 
			{	
				std::shared_ptr<Staff> doctor = nullptr;
				std::shared_ptr<Bag<Staff>> staffs = clinic->getStaffs();
				std::string doctorNamesNew = "Doctor_" + std::to_string(i + 1);
				std::string doctorSpecializationsNew = (i % 2 == 0) ? "Cardiology" : "Neurology";
				std::string newDoctorAddressesNew = "New Doctor Address " + std::to_string(i + 1);

				// Find a doctor by name, role, and specialty
				Bag<Staff>::const_iterator endit=staffs->end();
				for (Bag<Staff>::const_iterator it = staffs->begin(); it != endit; it++) 
				{
					std::string itName = (*it)->getName();
					std::string itRole = (*it)->getRole();
					std::string itSpecialization = (*it)->getSpecialty();

					// Match by name, role, and specialty
					if (itName == doctorNamesNew && itRole == doctorRolesNew && itSpecialization == newDoctorAddressesNew) 
					{
						doctor = (*it);
						break; 
					}
				}
				if (doctor != nullptr) 
				{
						// Change the facility for the found doctor
					clinic->changeDoctorFacility(doctor, newDoctorAddressesNew, doctor->getSpecialty());
				} 
			}
			end = std::chrono::high_resolution_clock::now();
			time6=std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
				
			// Coordinate admin staff - 7th operation
			const int numAdmins = Num_Elements;
			std::string adminRolesNew="Admin";
				
			start = std::chrono::high_resolution_clock::now();
			
			for (int i = 0; i < numAdmins; i++) 
			{
					// Start time to find the admin	
				std::shared_ptr<Staff> admin = nullptr;
				std::shared_ptr<Bag<Staff>> staffs = clinic->getStaffs();
				std::string adminNamesNew = "Admin_" + std::to_string(i + 1);
				std::string adminNewDepartmentsNew= (i % 2 == 0) ? "Finance" : "HR"; // Alternate departments
				std::string newAdminAddressesNew="New Admin Address " + std::to_string(i + 1);
					
							
				// Find the admin by name, role, and department
				Bag<Staff>::const_iterator endit=staffs->end();
				for (Bag<Staff>::const_iterator it = staffs->begin(); it != endit; it++) 
				{
					std::string itName = (*it)->getName();
					std::string itRole = (*it)->getRole();
					std::string itDepartment = (*it)->getDepartment();
					std::string adminRolesNew = "Admin"; // All roles are Admin		
					std::string newAdminAddressesNew= "New Admin Address " + std::to_string(i + 1);				
					if (itName == adminNamesNew && itRole == adminRolesNew && itDepartment == adminNewDepartmentsNew) 
					{
								admin = (*it);
								break; // Exit loop once the admin is found
					}
				}
				if (admin != nullptr) 
				{
					// Change the workplace for the found admin
					clinic->coordinateAdmin(admin, newAdminAddressesNew, adminNewDepartmentsNew);
				} 
			}
			end= std::chrono::high_resolution_clock::now();// creation time finishes
			time7=std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();					
			startTimedeletion= std::chrono::high_resolution_clock::now();
		}		
		endDeletion= std::chrono::high_resolution_clock::now();
		deletionTime= std::chrono::duration_cast<std::chrono::microseconds>(endDeletion - startTimedeletion).count();
		
		finalend=std::chrono::high_resolution_clock::now();
		
		csvFile << runNumber << "," << Num_Elements << ","<<time1<<","<<time2<<","<<time3<<","<<time4<<","<<time5<<","<<time6<<","<<time7<<","<<deletionTime<<std::endl;
		std::cout << "Operation Times: " << time1 << ", " << time2 << ", " << time3 << ", "  << time4 << ", " << time5 << ", " << time6 << ", " << time7 << std::endl;
		std::cout<<"Deletion Time: "<<deletionTime<<std::endl;
	}
}
//std::cout <<"creation time:"<<(std::chrono::duration_cast<std::chrono::microseconds>(end-start).count())<<"ms"<<std::endl;
//std::cout <<"final creation time:"<<(std::chrono::duration_cast<std::chrono::microseconds>(finalend-start).count())<<"ms"<<std::endl;
//std::cout <<"deletion time: "<<(std::chrono::duration_cast<std::chrono::microseconds>(endDeletion-startTimedeletion).count())<<"ms"<<std::endl;	
std::cout << "End of Program.." << std::endl;
csvFile.close();

    return 0;
}
