#include <iostream>
#include "data.hh"
#include "component_manager.hh"
#include "entity_manager.hh"
#include "system_manager.hh"


int main() {
  Health H1 = {0,0};
  Health H2 = {1,1};
  Health H3 = {2,2};
  Health H4 = {3,3};
  Health H5 = {4,4};

	// //test component remove
	// Component_data<Health> C;
  // C.add_data(0, H1);
	// C.display();
  // C.add_data(1, H2);
	// C.display();
  // C.add_data(2, H3);
	// C.display();
  // C.add_data(3, H4);
	// C.display();
	// C.remove_data(1);
	// C.display();
	// C.remove_data(3);
	// C.display();
  // C.add_data(4, H5);
	// C.display();


	// // Test component_manager
	// Component_manager CM;
	// CM.save_component<Health>(ECS_mask["Health"]);
	// CM.save_component<Transform>(ECS_mask["Transform"]);
	// // CM.save_component<Health>(ECS_mask["Health"]);
  //
	// CM.add_component<Health>(1, H1 ,ECS_mask["Health"]);
	// CM.add_component<Health>(2, H2 ,ECS_mask["Health"]);
  //
	// for (int i = 1; i < 3; ++i) {
	// 		auto tmp = CM.get_component<Health>(1, ECS_mask["Health"]);
	// 		std::cout << "Get entity 1 component H1 : " << tmp.current_health << "-" << tmp.max_health << std::endl;
	// }
  //
	// CM.add_component<Health>(1, H1, ECS_mask["Health"]);
	// CM.remove_component<Health>(1, ECS_mask["Health"]);
	// CM.remove_component<Health>(1, ECS_mask["Health"]);
  //
	// for (int i = 1; i < 3; ++i) {
	// 		auto tmp = CM.get_component<Health>(1, ECS_mask["Health"]);
	// 		std::cout << "Get entity 1 component H1 : " << tmp.current_health << "-" << tmp.max_health << std::endl;
	// }


	// // Test entity_manager
	// Entity_manager EM;
	// entity E1 = EM.create_entity();
	// entity E2 = EM.create_entity();
  //
	// EM.display();
  //
	// EM.set_ett_signature(E1,9);
	// EM.set_ett_signature(E2,12);
  //
	// EM.display();
  //
	// signature s = EM.get_ett_signature(E1);
	// std::cout << "E1 signature : " << s << std::endl;
  //
	// std::cout << "ajout bit position 32 au signature de E1 : " << std::endl;
	// EM.add_bit_to_ett_signature(E1, 32);
	// EM.display();
  //
	// std::cout << "supprime bit position 32 au signature de E1 : " << std::endl;
	// EM.remove_bit_to_ett_signature(E1, 32);
	// EM.display();
  //
	// std::cout << "Delete entity E1 : " << std::endl;
	// EM.delete_entity(E1);
	// EM.display();


	return 0;
}

