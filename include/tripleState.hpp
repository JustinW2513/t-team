#include "api.h"

enum class TripleStateMechStates {
		Middle,
		Index,
		High,
};

class TripleStateMech {

	private:
		pros::adi::Pneumatics middleGoalIndexerBottom;
		pros::adi::Pneumatics middleGoalIndexerTop;
		TripleStateMechStates state;

	public:
		TripleStateMech(std::uint8_t low_adi_port, std::uint8_t high_adi_port, TripleStateMechStates start_state = TripleStateMechStates::High)
			: middleGoalIndexerBottom(low_adi_port, false),
			  middleGoalIndexerTop(high_adi_port, false),
			  state(start_state) {
				setState(start_state);
			}

		void setState(TripleStateMechStates state) {
			this->state = state;

			if(state == TripleStateMechStates::High) {
				middleGoalIndexerBottom.set_value(LOW);
				middleGoalIndexerTop.set_value(LOW);
			}
			else if(state == TripleStateMechStates::Index) {
				middleGoalIndexerBottom.set_value(HIGH);
				middleGoalIndexerTop.set_value(LOW);	
			}
			else if(state == TripleStateMechStates::Middle) {
				middleGoalIndexerBottom.set_value(HIGH);
				middleGoalIndexerTop.set_value(HIGH);
			}
		}
};