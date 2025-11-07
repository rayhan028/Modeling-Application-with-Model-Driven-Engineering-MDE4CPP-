#include <chrono>
#include "abstractDataTypes/SubsetUnion.hpp"
#include "ecore/ecoreFactory.hpp"
#include "ecore/ecorePackage.hpp"
#include "ecore/EAnnotation.hpp"
#include "ecore/EAttribute.hpp"
#include "ecore/EClass.hpp"
#include "ecore/EClassifier.hpp"
#include "ecore/EReference.hpp"
#include "ecore/EStringToStringMapEntry.hpp"
#include "ecore/EStructuralFeature.hpp"
#include "ecore/EDataType.hpp"
#include "ecore/ENamedElement.hpp"
#include "ecore/EOperation.hpp"
#include "ecore/EModelElement.hpp"
#include "types/typesPackage.hpp"
#include "ecore/EParameter.hpp"
#include<iostream>
#include <fstream>
#include <string>

using namespace ecore;

bool isFileEmpty(const std::string& filename) 
{
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}

int main()
{
	int NUM_Object = 0;
	int runNumber = 0;
	std::ifstream configFile("C:/MDE4CPP/MDE4CPP/application/bin/ecoreinput.txt");
	if (!configFile.is_open())
	{
		std::cerr << "Error opening config.txt" << std::endl;
		return 1;
	}
	configFile >> NUM_Object >> runNumber;
	configFile.close();
	if (NUM_Object <= 0 || runNumber <= 0) 
	{
		std::cerr << "Invalid values" << std::endl;
		return 1;
	}
	
	std::ofstream creationFile("C:/MDE4CPP/MDE4CPP/application/runtimeEcore/EcoreCreation_times.csv", std::ios::app);
	std::ofstream deletionFile("C:/MDE4CPP/MDE4CPP/application/runtimeEcore/EcoreDeletion_times.csv", std::ios::app);

	if (!creationFile) 
	{
		std::cerr << "Error opening EcoreCreation_times.csv" << std::endl;
	}
	if (!deletionFile) 
	{
		std::cerr << "Error opening EcoreDeletion_times.csv" << std::endl;
	}

    // Check if creationFile is empty
    if (isFileEmpty("C:/MDE4CPP/MDE4CPP/application/runtimeEcore/EcoreCreation_times.csv")) 
	{
        creationFile << "RUN,Iteration,NUM_Object, Creation_Time_ms\n";
    }

    // Check if deletionFile is empty
    if (isFileEmpty("C:/MDE4CPP/MDE4CPP/application/runtimeEcore/EcoreDeletion_times.csv")) 
	{
        deletionFile << "RUN,Iteration,NUM_Object, Deletion_Time_ms\n";
    }
	
	std::chrono::time_point<std::chrono::high_resolution_clock> start, creation_start, creation_end, deletion_start, deletion_end, end;
	start = std::chrono::high_resolution_clock::now();
	
	{		//data types primitives
		const std::shared_ptr<ecore::EDataType> integerType = types::typesPackage::eInstance()->getInteger_Class();
		const std::shared_ptr<ecore::EDataType> stringType = types::typesPackage::eInstance()->getString_Class();
		const std::shared_ptr<ecore::EDataType> realType = types::typesPackage::eInstance()->getReal_Class();

		std::shared_ptr<ecorePackage> package = ecorePackage::eInstance();
		std::shared_ptr<ecoreFactory> factory = ecoreFactory::eInstance();
		end = std::chrono::high_resolution_clock::now();

		std::cout << "setup time: " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() <<"ms"<< std::endl;

		start = std::chrono::high_resolution_clock::now();

		end = std::chrono::high_resolution_clock::now();
		std::cout << "setup time for package: \n" << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() <<"ms"<< std::endl;
		
		const int numIterations = 10;
			
		std::cout << "- start iteration- \n";
		
		for(int j=0;j<numIterations;++j)
		{
			{				// root package
				std::shared_ptr<EPackage> rootPackage = factory->createEPackage();
				rootPackage->setName("InventorySystemExample_ecore");
				
				std::shared_ptr<Bag<ecore::EClassifier>> classifiers = rootPackage->getEClassifiers();
				creation_start = std::chrono::high_resolution_clock::now();// starting timing measurement here
				for(int i=0; i< NUM_Object; ++i)
				{
					
					std::shared_ptr<EClass> eClass_product = factory->createEClass_as_eClassifiers_in_EPackage(rootPackage);

					eClass_product->setName(std::string("Product")+std::to_string(i));
					// creating attribute of EClass Product
					std::shared_ptr<EAttribute> eAttribute_product_id = factory->createEAttribute_as_eStructuralFeatures_in_EClass(eClass_product);
					
				
					eAttribute_product_id->setName(std::string("productId") + std::to_string(i));
					eAttribute_product_id->setEType(integerType);
					eAttribute_product_id->setLowerBound(1); // Each product belongs to one category
					eAttribute_product_id->setUpperBound(1); // must belong to atleast one category
					
					std::shared_ptr<EAttribute> eAttribute_product_Name = factory->createEAttribute_as_eStructuralFeatures_in_EClass(eClass_product);
					eAttribute_product_Name->setName(std::string("productName") + std::to_string(i));
					eAttribute_product_Name->setEType(integerType);
					eAttribute_product_Name->setLowerBound(1); 
					eAttribute_product_Name->setUpperBound(1); 
					
					// Product EAnnotation
					std::shared_ptr<ecore::EAnnotation> annotation_product = factory->createEAnnotation_as_eAnnotations_in_EModelElement(eClass_product);
					annotation_product->setSource(std::string("Product")+std::to_string(i));

					// Product EOperation
					std::shared_ptr<EOperation> eOperation_getProductDetails = factory->createEOperation_as_eOperations_in_EClass(eClass_product);
					eOperation_getProductDetails->setName(std::string("getProductDetails") + std::to_string(i));
					eOperation_getProductDetails->setEType(stringType);

					// sample parameters for the operation
					std::shared_ptr<EParameter> eParameter_product = factory->createEParameter_as_eParameters_in_EOperation(eOperation_getProductDetails);
					eParameter_product->setName(std::string("product") + std::to_string(i));
					eParameter_product->setEType(eClass_product);

					// Creating Category class
					std::shared_ptr<EClass> eClass_category = factory->createEClass_as_eClassifiers_in_EPackage(rootPackage);
					
					//creating a reference to prdocut->category
					std::shared_ptr<EObject> product_category_ref = factory->create("EReference");
					std::shared_ptr<ecore::EReference> eReference_product_category;

					if (product_category_ref != nullptr)
					{
						eReference_product_category = std::dynamic_pointer_cast<EReference>(product_category_ref);
						if (eReference_product_category != nullptr)
						{
							eReference_product_category->setName(std::string("category") + std::to_string(i));
							eReference_product_category->setEType(eClass_category);  // Reference to Category class
							eReference_product_category->setLowerBound(1);  // Must have one category
							eReference_product_category->setUpperBound(1);  // Can only belong to one category

							std::shared_ptr<Bag<ecore::EReference>> references = eClass_product->getEReferences();
							references->add(eReference_product_category);
						}
					}
					eClass_category->setName(std::string("Category") + std::to_string(i));
					// Add attribute name to Category class
					std::shared_ptr<EAttribute> eAttribute_ID = factory->createEAttribute_as_eAttributes_in_EClass(eClass_category);
					eClass_category->setName(std::string("CategoryID") + std::to_string(i));
					eAttribute_ID->setEType(integerType); 
					eAttribute_ID->setLowerBound(0);
					eAttribute_ID->setUpperBound(1);

					// Add attribute description to Category class
					std::shared_ptr<EAttribute> eAttribute_description = factory->createEAttribute_as_eAttributes_in_EClass(eClass_category);
					eAttribute_description->setName(std::string("description") + std::to_string(i));
					eAttribute_description->setEType(stringType);
					eAttribute_description->setLowerBound(0);
					eAttribute_description->setUpperBound(1);

					// Category EOperation
					std::shared_ptr<EOperation> eOperation_getCategoryDetails = factory->createEOperation_as_eOperations_in_EClass(eClass_category);
					eOperation_getCategoryDetails->setName(std::string("getCategoryDetails") + std::to_string(i));
					eOperation_getCategoryDetails->setEType(stringType);

					std::shared_ptr<EParameter> eParameter_category = factory->createEParameter_as_eParameters_in_EOperation(eOperation_getCategoryDetails);
					eParameter_category->setName(std::string("category") + std::to_string(i));
					eParameter_category->setEType(eClass_category);

					// Category reference to products
					std::shared_ptr<EObject> o2 = factory->create("EReference");
					std::shared_ptr<ecore::EReference> eReference_category_product;
					if (o2 != nullptr)
					{
						eReference_category_product = std::dynamic_pointer_cast<EReference>(o2);
						if (eReference_category_product != nullptr)
						{
							//eReference_category_product->setName("products");
							eReference_category_product->setName(std::string("products") + std::to_string(i));
							eReference_category_product->setEType(eClass_product);
							eReference_category_product->setUpperBound(-1); // one category containes many product types
							std::shared_ptr<Bag<ecore::EReference>> references = eClass_category->getEReferences();
							references->add(eReference_category_product);
						}
					}
					// Category EAnnotation
					std::shared_ptr<ecore::EAnnotation> annotation_category = factory->createEAnnotation_as_eAnnotations_in_EModelElement(eClass_category);
					annotation_category->setSource(std::string("Category")+ std::to_string(i));

					// Creating StockItem class
					std::shared_ptr<EClass> eClass_stockItem  = factory->createEClass_as_eClassifiers_in_EPackage(rootPackage);
					eClass_stockItem->setName(std::string("StockItem") + std::to_string(i));

					// StockItem EOperation
					std::shared_ptr<EOperation> eOperation_getStockDetails = factory->createEOperation_as_eOperations_in_EClass(eClass_stockItem);
					eOperation_getStockDetails->setName(std::string("getStockDetails") + std::to_string(i));
					eOperation_getStockDetails->setEType(stringType);

					std::shared_ptr<EParameter> eParameter_stockItem = factory->createEParameter_as_eParameters_in_EOperation(eOperation_getStockDetails);
					eParameter_stockItem->setName(std::string("stockItem") + std::to_string(i));
					eParameter_stockItem->setEType(eClass_stockItem);

					// StockItem EAttributes
					std::shared_ptr<EAttribute> eAttribute_stockItem_name = factory->createEAttribute_as_eStructuralFeatures_in_EClass(eClass_stockItem);
					eAttribute_stockItem_name->setName(std::string("itemName") + std::to_string(i));
					eAttribute_stockItem_name->setEType(stringType);

					std::shared_ptr<EAttribute> eAttribute_stockItem_quantity = factory->createEAttribute_as_eStructuralFeatures_in_EClass(eClass_stockItem);
					//eAttribute_stockItem_quantity->setName("quantity");
					eAttribute_stockItem_quantity->setName(std::string("quantity") + std::to_string(i));
					eAttribute_stockItem_quantity->setEType(integerType);

					std::shared_ptr<EAttribute> eAttribute_stockItem_price = factory->createEAttribute_as_eStructuralFeatures_in_EClass(eClass_stockItem);
					//eAttribute_stockItem_price->setName("price");
					eAttribute_stockItem_price->setName(std::string("price") + std::to_string(i));
					eAttribute_stockItem_price->setEType(realType);

					// Create reference to Category class
					std::shared_ptr<EObject> eObject1_reference = factory->create("EReference");
					std::shared_ptr<ecore::EReference> eReference_stockItem_category;
					if (eObject1_reference != nullptr)
					{
						// Casting eObject1_reference to a new EReference instance
						eReference_stockItem_category = std::dynamic_pointer_cast<EReference>(eObject1_reference);
						if (eReference_stockItem_category != nullptr)
						{
							eReference_stockItem_category->setName(std::string("category") + std::to_string(i));
							// Reference will be of type "Category"
							eReference_stockItem_category->setEType(eClass_category);
							eReference_stockItem_category->setUpperBound(1); // 1-to-1 reference for simplicity

							std::shared_ptr<Bag<ecore::EReference>> references2 = eClass_stockItem->getEReferences();
							references2->add(eReference_stockItem_category);
						}
					}
					
					//creating supplier class
					std::shared_ptr<EClass> eClass_supplier = factory->createEClass_as_eClassifiers_in_EPackage(rootPackage);
					eClass_supplier->setName(std::string("Supplier") + std::to_string(i));
					// Supplier EOperation
					std::shared_ptr<EOperation> eOperation_getSupplierInfo = factory->createEOperation_as_eOperations_in_EClass(eClass_supplier);

					eOperation_getSupplierInfo->setName(std::string("getSupplierInfo") + std::to_string(i));
					eOperation_getSupplierInfo->setEType(stringType);

					// Supplier EParameter for the supplier object

					std::shared_ptr<EParameter> eParameter_supplier = factory->createEParameter_as_eParameters_in_EOperation(eOperation_getSupplierInfo);
					eParameter_supplier->setName(std::string("supplier") + std::to_string(i));
					eParameter_supplier->setEType(eClass_supplier);

					// Supplier EAttribute for supplier name
					std::shared_ptr<EAttribute> eAttribute_supplier_name = factory->createEAttribute_as_eStructuralFeatures_in_EClass(eClass_supplier);
					eAttribute_supplier_name->setName(std::string("supplierName") + std::to_string(i));
					eAttribute_supplier_name->setEType(stringType);

					// Supplier EAttribute for supplier contact
					std::shared_ptr<EAttribute> eAttribute_supplier_contact = factory->createEAttribute_as_eStructuralFeatures_in_EClass(eClass_supplier);
					eAttribute_supplier_contact->setName(std::string("supplierContact") + std::to_string(i));
					eAttribute_supplier_contact->setEType(stringType);

					// Forward declaration
					std::shared_ptr<ecore::EReference> eReference_supplier_product;
					if (eObject1_reference != nullptr)
					{
						eReference_supplier_product = std::dynamic_pointer_cast<EReference>(eObject1_reference);
						if (eReference_supplier_product != nullptr)
						{
							// Reference will be of type "Product"
							eReference_supplier_product->setName(std::string("supplies") + std::to_string(i));
							eReference_supplier_product->setEType(eClass_product);
													// -1 is used to set a [0..*] multiplicity
							eReference_supplier_product->setUpperBound(-1);
													// Add the reference to the Supplier class
							std::shared_ptr<Bag<ecore::EReference>> references = eClass_supplier->getEReferences();
							references->add(eReference_supplier_product);
						 }
					}
					// Supplier EAnnotation
					std::shared_ptr<ecore::EAnnotation> annotation_supplier = factory->createEAnnotation_as_eAnnotations_in_EModelElement(eClass_supplier);
					annotation_supplier->setSource(("supplier")+ std::to_string(i));

					// creating an Order class
					std::shared_ptr<EClass> eClass_order = factory->createEClass_as_eClassifiers_in_EPackage(rootPackage);
					eClass_order->setName(std::string("Order") + std::to_string(i));

					// Order EOperation
					std::shared_ptr<EOperation> eOperation_placeOrder = factory->createEOperation_as_eOperations_in_EClass(eClass_order);
					//eOperation_placeOrder->setName("placeOrder");
					eOperation_placeOrder->setName(std::string("placeOrder") + std::to_string(i));
					eOperation_placeOrder->setEType(integerType);

					std::shared_ptr<EParameter> eParameter_order = factory->createEParameter_as_eParameters_in_EOperation(eOperation_placeOrder);
					eParameter_order->setName(std::string("order") + std::to_string(i));
					eParameter_order->setEType(eClass_order);

					// Order attributes
					std::shared_ptr<EAttribute> eAttribute_orderNum = factory->createEAttribute_as_eStructuralFeatures_in_EClass(eClass_order);
					eAttribute_orderNum->setName(std::string("orderNum") + std::to_string(i));
					eAttribute_orderNum->setEType(stringType);

					std::shared_ptr<EAttribute> eAttribute_orderDate = factory->createEAttribute_as_eStructuralFeatures_in_EClass(eClass_order);
					eAttribute_orderDate->setName(std::string("orderDate") + std::to_string(i));
					eAttribute_orderDate->setEType(stringType);

					std::shared_ptr<EAttribute> eAttribute_orderStatus = factory->createEAttribute_as_eStructuralFeatures_in_EClass(eClass_order);
					eAttribute_orderStatus->setName(std::string("orderStatus") + std::to_string(i));
					eAttribute_orderStatus->setEType(stringType);

					// Order reference to Product
					std::shared_ptr<EReference> eReference_order_product = factory->createEReference_as_eStructuralFeatures_in_EClass(eClass_order);
					eReference_order_product->setName(std::string("products") + std::to_string(i));
					eReference_order_product->setEType(eClass_product); //
					eReference_order_product->setUpperBound(-1);

					/// Order reference to StockItem
					std::shared_ptr<EReference> eReference_order_stockItem = factory->createEReference_as_eStructuralFeatures_in_EClass(eClass_order);
					eReference_order_stockItem->setName(std::string("stockItems") + std::to_string(i));
					eReference_order_stockItem->setEType(eClass_stockItem); // Linking to StockItem class
					eReference_order_stockItem->setUpperBound(-1); // One order can have multiple stock items

					// Order EAnnotation
					std::shared_ptr<ecore::EAnnotation> annotation_order = factory->createEAnnotation_as_eAnnotations_in_EModelElement(eClass_order);
					annotation_order->setSource(("order")+ std::to_string(i));
							
				}
				creation_end = std::chrono::high_resolution_clock::now();
				//std::cout<<classifiers->size();
				deletion_start = std::chrono::high_resolution_clock::now();			
			//classifiers->clear();
			}

			deletion_end = std::chrono::high_resolution_clock::now();
			creationFile << runNumber <<","<< j + 1 << "," << NUM_Object << "," << std::chrono::duration_cast<std::chrono::milliseconds>(creation_end - creation_start).count() << "\n";
            deletionFile << runNumber <<","<< j + 1 << "," << NUM_Object << "," << std::chrono::duration_cast<std::chrono::milliseconds>(deletion_end - deletion_start).count() << "\n";
			
			// Write to the CSV file		    
			//csvFile << runNumber << "," << NUM_Object << "," << j + 1 << "," << std::chrono::duration_cast<std::chrono::milliseconds>(creation_end - creation_start).count() << "," << std::chrono::duration_cast<std::chrono::milliseconds>(deletion_end - deletion_start).count() << "\n";
			
			std::cout << "Time to create " << " defined meta-models: " << std::chrono::duration_cast<std::chrono::milliseconds>(creation_end - creation_start).count() << ";ms ;;" <<"Deletion Time: "<<std::chrono::duration_cast<std::chrono::milliseconds>(deletion_end - deletion_start).count()<<";ms;"<< std::endl;
		}	
		//csvFile.close();
	}
	std::cout << "Total execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(deletion_end - start).count() << "ms" << std::endl;
	creationFile.close();
    deletionFile.close();
	//runNumber++;

	return 0;
}
