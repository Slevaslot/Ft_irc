# FT_IRC

## Description

Ce projet implémente un serveur IRC simple. Il permet aux utilisateurs de se connecter, de rejoindre des channels, d'envoyer des messages et de gerer les canaux de discussion en tant qu'operateur.

## Installation

1. **Cloner le dépôt :**

   ```bash
   git clone https://github.com/slevaslo/Ft_irc.git
   cd Ft_irc
   ```

2. **Compiler le serveur :**

   ```bash
   make
   ```

## Utilisation

1. **Lancer le serveur :**

   ```bash
   ./ircserv <port> <password>
   ```

   Par défaut, le serveur écoute sur le port 4444. Vous pouvez changer le port en modifiant le code source.

2. **Se connecter :**

   Utilisez un client IRC comme [Irssi](https://irssi.org) ou [HexChat](https://hexchat.github.io) pour vous connecter au serveur. Par exemple, avec Irssi :

   ```bash
   irssi
   /connect localhost 4444 mdp
   ```

## Commandes IRC Supportées

1. **Commandes Utilisateurs Basiques**

- `/NICK <nickname>` : Définir votre pseudo.
- `/JOIN <channel>` : Rejoindre un channel.
- `/PART <channel>` : Quitter un channel.
- `/PRIVMSG <target> <message>` : Envoyer un message.
- `/LIST` : Afficher la liste des channels.

2. **Commandes Operateurs**

- `/KICK ` : Ejecter un client du channel.
- `/INVITE ` : Inviter un client au channel.
- `/TOPIC ` : Modifier ou afficher le thème du channel.
- `/MODE ` : Changer le mode du channel :
	- i : Définir/supprimer le canal sur invitation uniquement
	- t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
	- k : Définir/supprimer la clé du canal (mot de passe)
	- o : Donner/retirer le privilège de l’opérateur de canal
	- l : Définir/supprimer la limite d’utilisateurs pour le canal

## Créateurs

- **Souleimane Alexis LEVASLOT** - [slevaslot](https://github.com/slevaslot)
- **Pablo DOSSO DAUTAIS** - [pdosso-d](https://github.com/pdosso-d)
