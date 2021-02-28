#include "Genetic_al.h"

void AI::Genetic_al::init(int size)
{
	this->distribution_0 = std::uniform_int_distribution<int>(0, 10000);
	this->distribution_1 = std::uniform_int_distribution<int>(0, 20000);

	this->population.reserve(size);
	for (int i = 0; i < size; i++) {
		Weight new_weight;
		new_weight.average_height = this->rand_1();
		new_weight.average_height_top_half = this->rand_1();
		new_weight.average_height_top_quarter = this->rand_1();
		new_weight.bumpiness = this->rand_1();
		new_weight.bumpiness_s = this->rand_1();
		new_weight.well = this->rand_1();
		new_weight.well_s = this->rand_1();
		new_weight.hole = this->rand_1();
		new_weight.overhang = this->rand_1();
		new_weight.block_above_hole = this->rand_1();
		new_weight.block_above_hole_s = this->rand_1();
		for (int i = 0; i < 10; i++) {
			new_weight.column_height[i] = this->rand_1();
			new_weight.column_well[i] = this->rand_1();
			if (i < 3)
				new_weight.structure[i] = this->rand_1();
		}
		new_weight.waste_structure = this->rand_1();
		new_weight.b2b = this->rand_1();
		new_weight.ren = this->rand_1();
		new_weight.line_sent = this->rand_1();
		new_weight.perfect_clear = 10;
		new_weight.t_spin_1 = this->rand_0();
		new_weight.t_spin_2 = this->rand_0();
		new_weight.t_spin_3 = this->rand_0();
		new_weight.tetris = this->rand_0();
		new_weight.burn_1 = - this->rand_0();
		new_weight.burn_2 = - this->rand_0();
		new_weight.burn_3 = - this->rand_0();
		new_weight.waste_time = this->rand_1();

		this->population.push_back(new_weight);
	}
}

void AI::Genetic_al::save()
{
	std::ofstream file;
	file.open("weight_data.txt");

	file << "#include \"Genetic_al_gen.h\"" << "\n" << "\n";

	file << "std::vector<std::vector<int>> AI::Genetic_al_gen::data = {" << "\n";

	for (int i = 0; i < (int)this->population.size(); i++) {
		file << this->serialize(this->population[i]);
		if (i != (int)this->population.size() - 1)
			file << ", " << "\n";
	}

	file << "\n};" << "\n";

	file.close();
}

void AI::Genetic_al::set()
{
	for (int i = 0; i < (int)AI::Genetic_al_gen::data.size(); i++) {
		this->population[i].average_height = AI::Genetic_al_gen::data[i][0];
		this->population[i].average_height_top_half = AI::Genetic_al_gen::data[i][1];
		this->population[i].average_height_top_quarter = AI::Genetic_al_gen::data[i][2];
		this->population[i].bumpiness = AI::Genetic_al_gen::data[i][3];
		this->population[i].bumpiness_s = AI::Genetic_al_gen::data[i][4];
		this->population[i].well = AI::Genetic_al_gen::data[i][5];
		this->population[i].well_s = AI::Genetic_al_gen::data[i][6];
		this->population[i].hole = AI::Genetic_al_gen::data[i][7];
		this->population[i].overhang = AI::Genetic_al_gen::data[i][8];
		this->population[i].block_above_hole = AI::Genetic_al_gen::data[i][9];
		this->population[i].block_above_hole_s = AI::Genetic_al_gen::data[i][10];
		for (int k = 0; k < 10; k++) {
			this->population[i].column_height[k] = AI::Genetic_al_gen::data[i][11 + k];
			this->population[i].column_well[k] = AI::Genetic_al_gen::data[i][21 + k];
			if (k < 3)
				this->population[i].structure[k] = AI::Genetic_al_gen::data[i][31 + k];
		}
		this->population[i].waste_structure = AI::Genetic_al_gen::data[i][34];
		this->population[i].b2b = AI::Genetic_al_gen::data[i][35];
		this->population[i].ren = AI::Genetic_al_gen::data[i][36];
		this->population[i].line_sent = AI::Genetic_al_gen::data[i][37];
		this->population[i].perfect_clear = 10.0f;
		this->population[i].t_spin_1 = AI::Genetic_al_gen::data[i][39];
		this->population[i].t_spin_2 = AI::Genetic_al_gen::data[i][40];
		this->population[i].t_spin_3 = AI::Genetic_al_gen::data[i][41];
		this->population[i].tetris = AI::Genetic_al_gen::data[i][42];
		this->population[i].burn_1 = AI::Genetic_al_gen::data[i][43];
		this->population[i].burn_2 = AI::Genetic_al_gen::data[i][44];
		this->population[i].burn_3 = AI::Genetic_al_gen::data[i][45];
		this->population[i].waste_time = AI::Genetic_al_gen::data[i][46];
	}
}

std::string AI::Genetic_al::serialize(Weight _weight)
{
	std::string result;
	result.append("{ ");

	result.append(std::to_string(_weight.average_height));
	result.append("f, ");
	result.append(std::to_string(_weight.average_height_top_half));
	result.append("f, ");
	result.append(std::to_string(_weight.average_height_top_quarter));
	result.append("f, ");
	result.append(std::to_string(_weight.bumpiness));
	result.append("f, ");
	result.append(std::to_string(_weight.bumpiness_s));
	result.append("f, ");
	result.append(std::to_string(_weight.well));
	result.append("f, ");
	result.append(std::to_string(_weight.well_s));
	result.append("f, ");
	result.append(std::to_string(_weight.hole));
	result.append("f, ");
	result.append(std::to_string(_weight.overhang));
	result.append("f, ");
	result.append(std::to_string(_weight.block_above_hole));
	result.append("f, ");
	result.append(std::to_string(_weight.block_above_hole_s));
	result.append("f, ");
	for (int i = 0; i < 10; i++) {
		result.append(std::to_string(_weight.column_height[i]));
		result.append("f, ");
	}
	for (int i = 0; i < 10; i++) {
		result.append(std::to_string(_weight.column_well[i]));
		result.append("f, ");
	}
	for (int i = 0; i < 3; i++) {
		result.append(std::to_string(_weight.structure[i]));
		result.append("f, ");
	}
	result.append(std::to_string(_weight.waste_structure));
	result.append("f, ");
	result.append(std::to_string(_weight.b2b));
	result.append("f, ");
	result.append(std::to_string(_weight.ren));
	result.append("f, ");
	result.append(std::to_string(_weight.line_sent));
	result.append("f, ");
	result.append(std::to_string(_weight.perfect_clear));
	result.append("f, ");
	result.append(std::to_string(_weight.t_spin_1));
	result.append("f, ");
	result.append(std::to_string(_weight.t_spin_2));
	result.append("f, ");
	result.append(std::to_string(_weight.t_spin_3));
	result.append("f, ");
	result.append(std::to_string(_weight.tetris));
	result.append("f, ");
	result.append(std::to_string(_weight.burn_1));
	result.append("f, ");
	result.append(std::to_string(_weight.burn_2));
	result.append("f, ");
	result.append(std::to_string(_weight.burn_3));
	result.append("f, ");
	result.append(std::to_string(_weight.waste_time));

	result.append(" }");

	return result;
}

AI::Weight AI::Genetic_al::mutate(Weight w1, Weight w2)
{
	Weight new_weight;

	new_weight.average_height = this->v_mutate(w1.average_height, w2.average_height);
	new_weight.average_height_top_half = this->v_mutate(w1.average_height_top_half, w2.average_height_top_half);
	new_weight.average_height_top_quarter = this->v_mutate(w1.average_height_top_quarter, w2.average_height_top_quarter);
	new_weight.bumpiness = this->v_mutate(w1.bumpiness, w2.bumpiness);
	new_weight.bumpiness_s = this->v_mutate(w1.bumpiness_s, w2.bumpiness_s);
	new_weight.well = this->v_mutate(w1.well, w2.well);
	new_weight.well_s = this->v_mutate(w1.well_s, w2.well_s);
	new_weight.hole = this->v_mutate(w1.hole, w2.hole);
	new_weight.overhang = this->v_mutate(w1.overhang, w2.overhang);
	new_weight.block_above_hole = this->v_mutate(w1.block_above_hole, w2.block_above_hole);
	new_weight.block_above_hole_s = this->v_mutate(w1.block_above_hole_s, w2.block_above_hole_s);
	for (int i = 0; i < 10; i++) {
		new_weight.column_height[i] = this->v_mutate(w1.column_height[i], w2.column_height[i]);
		new_weight.column_well[i] = this->v_mutate(w1.column_well[i], w2.column_well[i]);
		if (i < 3) {
			new_weight.structure[i] = this->v_mutate(w1.structure[i], w2.structure[i]);
		}
	}
	new_weight.waste_structure = this->v_mutate(w1.waste_structure, w2.waste_structure);
	new_weight.b2b = this->v_mutate(w1.b2b, w2.b2b);
	new_weight.ren = this->v_mutate(w1.ren, w2.ren);
	new_weight.line_sent = this->v_mutate(w1.line_sent, w2.line_sent);
	new_weight.perfect_clear = 10.0f;
	new_weight.t_spin_1 = this->v_mutate(w1.t_spin_1, w2.t_spin_1);
	new_weight.t_spin_2 = this->v_mutate(w1.t_spin_2, w2.t_spin_2);
	new_weight.t_spin_3 = this->v_mutate(w1.t_spin_3, w2.t_spin_3);
	new_weight.tetris = this->v_mutate(w1.tetris, w2.tetris);
	new_weight.burn_1 = this->v_mutate(w1.burn_1, w2.burn_1);
	new_weight.burn_2 = this->v_mutate(w1.burn_2, w2.burn_2);
	new_weight.burn_3 = this->v_mutate(w1.burn_3, w2.burn_3);
	new_weight.waste_time = this->v_mutate(w1.waste_time, w2.waste_time);

	return new_weight;
}

float AI::Genetic_al::v_mutate(float w1, float w2)
{
	int rand_1_100 = rand() % 100 + 1;
	if (rand_1_100 <= 40) {
		return w1;
	}
	else if (rand_1_100 <= 80) {
		return w2;
	}
	else {
		return ((w1 + w2) / 2);
	}
}

float AI::Genetic_al::rand_1()
{
	int a = this->distribution_1(AI::Genetic_al::generator) - 10000;
	float b = (float)a / 10000.0f;
	return b;
}

float AI::Genetic_al::rand_0()
{
	int a = this->distribution_0(AI::Genetic_al::generator);
	float b = (float)a / 10000.0f;
	return b;
}
