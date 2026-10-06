/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089
#define TAILLE_MESSAGE 1024

int renvoie_message(int client_socket_fd, const char *message);
int recois_envoie_message(int client_socket_fd, char *message);

#endif
