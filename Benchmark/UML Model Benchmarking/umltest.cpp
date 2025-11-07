static int run=1;
bool isFileEmpty(const std::string& filename) 
{
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}

std::ofstream creationFile("umlOperation_times.csv", std::ios::app);

// Check if creationFile is empty
if (isFileEmpty("umlOperation_times.csv")) 
{
    creationFile << "RUN,Iteration,NUM_Element, Creation_Time_ms, Deletion_Time_ms\n";
}

std::chrono::time_point<std::chrono::high_resolution_clock>start,end,startTimedeletion,endDeletion,finalend;
{
	//Create Model Factory and Package
	std::shared_ptr<ClinicModelFactory> factory = ClinicModelFactory::eInstance();
	std::shared_ptr<ClinicModelPackage> package = ClinicModelPackage::eInstance();

	const int numStaffTypes = 6; // Number of staff types
	// Staff types and their respective attributes
	std::string staffRoles[numStaffTypes] = {"Doctor", "Nurse", "Admin", "Doctor", "Nurse", "Admin"};
	std::string doctorSpecialties[numStaffTypes] = {"Cardiology", "", "", "Neurology", "", ""}; // Specialties for doctors
	std::string nurseWards[numStaffTypes] = {"", "ICU", "", "", "Pediatrics", ""}; // Wards for nurses
	std::string adminDepartments[numStaffTypes] = {"", "", "HR", "", "", "Finance"}; // Departments for admins
	
	// Adding staff to the clinic
	start = std::chrono::high_resolution_clock::now();
	{
		std::shared_ptr<Clinic> clinic = factory->createClinic();
		std::string clinicName = "Sample Clinic"; // Example clinic 
		clinic->setClinicName(clinicName);
			
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
			if (staffRole == "Doctor") 
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
		std::cout << "Time taken to add all staff: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "ms" << std::endl;
			
		const int numSpecializedFacilities = 5;
		std::string specializedFacilityAddresses[numSpecializedFacilities] = {"SpecFacility Address 1", "SpecFacility Address 2", "SpecFacility Address 3", "SpecFacility Address 4", "SpecFacility Address 5"};
		std::string specializedFacilitySpecializations[numSpecializedFacilities] = {"Cardiology", "Neurology", "Oncology", "Pediatrics", "Radiology"};

		const int numGeneralFacilities = 5;
		std::string generalFacilityAddresses[numGeneralFacilities] = {"GenFacility Address 1", "GenFacility Address 2", "GenFacility Address 3", "GenFacility Address 4", "GenFacility Address 5"};

		const int numAdminFacilities = 5;
		std::string adminFacilityAddresses[numAdminFacilities] = {"AdminFacility Address 1", "AdminFacility Address 2", "AdminFacility Address 3", "AdminFacility Address 4", "AdminFacility Address 5"};
		std::string adminFacilityDepartments[numAdminFacilities] = {"HR", "Finance", "IT", "Marketing", "Admissions"};

		// Start of dynamic facility addition
		// Add Specialized Facilities
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < Num_Elements; i++) 
		{	
			std::shared_ptr<SpecializedFacility> sfacility = factory->createSpecializedFacility_as_specialfacilities_in_Clinic(clinic);
			sfacility->setAddress(specializedFacilityAddresses[i % numSpecializedFacilities]);
			sfacility->setSpecialization(specializedFacilitySpecializations[i % numSpecializedFacilities]);
				
		}
		end = std::chrono::high_resolution_clock::now();
		std::cout << "Time taken to add all specialized facilities: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "ms" << std::endl;

		// Add General Facilities
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < Num_Elements; i++) 
		{
			std::shared_ptr<GeneralFacility> gfacility = factory->createGeneralFacility_as_generalfacilities_in_Clinic(clinic);
			gfacility->setAddress(generalFacilityAddresses[i % numGeneralFacilities]);
		}
		end = std::chrono::high_resolution_clock::now();
		std::cout << "Time taken to add all generalfacility: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "ms" << std::endl;
			
		// Add Admin Facilities
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < Num_Elements; i++) 
		{
			std::shared_ptr<AdministrationFacility> adfacility = factory->createAdministrationFacility_as_employAdmins_in_Clinic(clinic);
			adfacility->setAddress(adminFacilityAddresses[i % numAdminFacilities]);
			adfacility->setAdminDept(adminFacilityDepartments[i % numAdminFacilities]);	
		}
		end = std::chrono::high_resolution_clock::now();
		std::cout << "Time taken to add all adminfacility: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "ms" << std::endl;
			
		// Changing workplace of nurses
		const int Num_Nurses = Num_Elements; // Number of nurses
		std::string nurseNames[Num_Nurses]; // Names of nurses
		std::string nurseRoles[Num_Nurses]; // Roles (all nurses)
		std::string nurseNewWards[Num_Nurses]; // Current wards of nurses
		std::string newNurseAddresses[Num_Nurses]; // New facility addresses

		// Generate nurse names and roles dynamically
		for (int i = 0; i < Num_Nurses; i++) 
		{
			nurseNames[i] = "Nurse_" + std::to_string(i + 1);
			nurseRoles[i] = "Nurse"; // All roles are Nurse
			// Assign wards and addresses dynamically if needed
			nurseNewWards[i] = (i % 3 == 0) ? "ICU" : (i % 3 == 1) ? "Pediatrics" : "Emergency";
			newNurseAddresses[i] = "New Address " + std::to_string(i + 1);
		}

		// Change nurse facilities
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < Num_Nurses; i++) 
		{	
			std::shared_ptr<Staff> nurse = nullptr;
			std::shared_ptr<Bag<Staff>> staffs = clinic->getStaffs();
					
			// Find the nurse by name, role, and ward
			Bag<Staff>::const_iterator endit=staffs->end();
			for (Bag<Staff>::const_iterator it = staffs->begin(); it != endit; it++) 
			{
				std::string itName = (*it)->getName();
				std::string itRole = (*it)->getRole();
				std::string itWard = (*it)->getWard();
									
				if (itName == nurseNames[i] && itRole == nurseRoles[i] && itWard == nurseNewWards[i]) 
				{
					nurse = (*it);
					break; // Exit loop once the nurse is found
				}
			}

			if (nurse != nullptr) 
			{
				clinic->changeNurseFacility(nurse, newNurseAddresses[i]);
				// std::cout << "Nurse " << nurseNames[i] << " assigned to new facility: " << newNurseAddresses[i] << std::endl;
			} 
		}
		end = std::chrono::high_resolution_clock::now();
		std::cout << "Time taken to find nurses and changing workplace: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "ms" << std::endl;
			
		// Changing facility of doctors
		const int numDoctors = Num_Elements; // Number of doctors
		std::string doctorNames[numDoctors]; // Names 
		std::string doctorRoles[numDoctors]; // Roles 
		std::string doctorSpecializations[numDoctors]; // Specializations
		std::string newDoctorAddresses[numDoctors]; // New addresses

		// Generate doctor names, roles, and specializations
		for (int i = 0; i < numDoctors; i++) 
		{
			doctorNames[i] = "Doctor_" + std::to_string(i + 1);
			doctorRoles[i] = "Doctor"; // All roles are Doctor
			// Assign specializations dynamically
			doctorSpecializations[i] = (i % 2 == 0) ? "Cardiology" : "Neurology"; // Alternate specializations
			newDoctorAddresses[i] = "New Doctor Address " + std::to_string(i + 1);
		}

		// Change doctor facilities
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < numDoctors; i++) 
		{	
			std::shared_ptr<Staff> doctor = nullptr;
			std::shared_ptr<Bag<Staff>> staffs = clinic->getStaffs();

			// Find a doctor by name, role, and specialty
			Bag<Staff>::const_iterator endit=staffs->end();
			for (Bag<Staff>::const_iterator it = staffs->begin(); it != endit; it++) 
			{
				std::string itName = (*it)->getName();
				std::string itRole = (*it)->getRole();
				std::string itSpecialization = (*it)->getSpecialty();

				// Match by name, role, and specialty
				if (itName == doctorNames[i] && itRole == doctorRoles[i] && itSpecialization == doctorSpecializations[i]) 
				{
					doctor = (*it);
						break; 
				}
			}
			if (doctor != nullptr) 
			{
				// Change the facility for the found doctor
				clinic->changeDoctorFacility(doctor, newDoctorAddresses[i], doctor->getSpecialty());
			} 
		}
		end = std::chrono::high_resolution_clock::now();
		std::cout << "Time taken to find doctor and change doctor workplace: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "ms" << std::endl;
			
		// Changing admins' workplaces
		const int numAdmins = Num_Elements; // Number of admins to coordinate
		std::string adminNames[numAdmins]; // Names 
		std::string adminRoles[numAdmins]; // Roles 
		std::string adminNewDepartments[numAdmins]; // New departments for admins
		std::string newAdminAddresses[numAdmins]; // New facility addresses

		// Generate admin names, roles, and departments
		for (int i = 0; i < numAdmins; i++) 
		{
			adminNames[i] = "Admin_" + std::to_string(i + 1); // 
			adminRoles[i] = "Admin"; // All roles are Admin
			adminNewDepartments[i] = (i % 2 == 0) ? "Finance" : "HR"; // Alternate departments
			newAdminAddresses[i] = "New Admin Address " + std::to_string(i + 1); // New addresses
		}
		// Coordinate admin staff
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < numAdmins; i++) 
		{
			// Start time to find the admin	
			std::shared_ptr<Staff> admin = nullptr;
			std::shared_ptr<Bag<Staff>> staffs = clinic->getStaffs();
					
			// Find the admin by name, role, and department
			Bag<Staff>::const_iterator endit=staffs->end();
			for (Bag<Staff>::const_iterator it = staffs->begin(); it != endit; it++) 
			{
				std::string itName = (*it)->getName();
				std::string itRole = (*it)->getRole();
				std::string itDepartment = (*it)->getDepartment();
									
				if (itName == adminNames[i] && itRole == adminRoles[i] && itDepartment == adminNewDepartments[i]) 
				{
						admin = (*it);
						break; // Exit loop once the admin is found
				}
			}
			if (admin != nullptr) 
			{
				// Change the workplace for the found admin
				clinic->coordinateAdmin(admin, newAdminAddresses[i], adminNewDepartments[i]);
			} 
		}
		end= std::chrono::high_resolution_clock::now();// creation time finishes
		startTimedeletion= std::chrono::high_resolution_clock::now();
	}
	endDeletion= std::chrono::high_resolution_clock::now();
}
finalend=std::chrono::high_resolution_clock::now();
std::cout <<"creation time:"<<(std::chrono::duration_cast<std::chrono::microseconds>(end-start).count())<<"ms"<<std::endl;
std::cout <<"final creation time:"<<(std::chrono::duration_cast<std::chrono::microseconds>(finalend-start).count())<<"ms"<<std::endl;
std::cout <<"deletion time: "<<(std::chrono::duration_cast<std::chrono::microseconds>(endDeletion-startTimedeletion).count())<<"ms"<<std::endl;
std::cout << "// of Program.." << std::endl;
	
creationFile << run <<"," << "," << NUM_Object << "," << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << ","<<std::chrono::duration_cast<std::chrono::microseconds>(endDeletion-startTimedeletion).count()<<std::endl;
creationFile.close();

