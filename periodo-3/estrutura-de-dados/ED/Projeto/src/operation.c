#include <stdio.h>
#include "./lib/operation.h"
#include "./lib/graph.h"

#define STANDARD_USER_NAME_LENGTH 20
#define EQUAL_NAMES 0

void userGetFollowers(graph *grp, user user_name) {

}

void userGetFollowing(graph *grp, user user_name) {

}

void userListNoFollowers(graph *grp) {

}

void userListNoFollowing(graph *grp) {

}

void userListByFollowersAmount(graph *grp) {

}

void userCreate(graph *grp) {

}

void userFollow(graph *grp, user first_user, user second_user) {

}

void userUnfollow(graph *grp, user first_user, user second_user) {

}

/*
void print(graph *grp) {
	vertex *vert = NULL;
	edge *ed = NULL;

	vert = grp->first_vertex;
	printf("Grafo: ->\n");
	while (vert) {
		printf("    %d:", vert->label);

		ed = vert->first_edge;
		while (ed) {
			printf("(%d)", ed->destiny->label);
			ed = ed->next_edge;
		}
		printf("\n");
		vert = vert->next_vertex;
	}
}

void run() {
	int networkOnline = ONLINE;
	char option;

	printf("\e[1J\e[1H_______________________  BEM-VINDO AO GRAFNET  _______________________\n\n");

	do {
		printf(
		"----------------------------------------------------------------------\n"
		" [ 1 ] Selecionar um usuário e listar os seus seguidores\n"
		" [ 2 ] Selecionar um usuário e listar os seus seguidos\n"
		" [ 3 ] Listar usuários que não são seguidos por ninguém\n"
		" [ 4 ] Listar usuários que não seguem ninguém\n"
		" [ 5 ] Listar todos os usuários ordenados por n° seguidores\n"
		" [ 6 ] Inserir um novo usuário\n"
		" [ 7 ] Selecionar dois usuários e fazer o primeiro seguir o segundo\n"
		" [ 8 ] Selecionar dois usuários e fazer o primeiro deixar de seguir o segundo\n"
		" [ 9 ] Sair\n"
		"----------------------------------------------------------------------\n+> "
		);

		scanf(" %c", &option);
		printf("\e[1J\e[1H");
		switch (option) {
			case '1':
			//userGetFollowers(graph *grp, user user_name);
			break;
			case '2':
			//userGetFollowing(graph *grp, user user_name);
			break;
			case '3':
			//userListNoFollowers(graph *grp);
			break;
			case '4':
			//userListNoFollowing(graph *grp);
			break;
			case '5':
			//userListByFollowersAmount(graph *grp);
			break;
			case '6':
			//userCreate(graph *grp);
			break;
			case '7':
			//userFollow(graph *grp, user first_user, user second_user);
			break;
			case '8':
			//userUnfollow(graph *grp, user first_user, user second_user);
			break;
			case '9':
			networkOnline = OFFLINE;
			break;
			default:
				printf("! OPÇÃO INVÁLIDA !\n");
		}
	} while (networkOnline);
}
*/
