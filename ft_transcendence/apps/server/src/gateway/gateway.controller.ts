import { OnModuleInit } from '@nestjs/common';
import { WebSocketGateway, WebSocketServer } from '@nestjs/websockets';
import { Server } from 'socket.io';
import { GameData } from '@server/types/types';
import { PongData } from '@server/classes/Classes';
import {
  checkBallBoundsY,
  checkBallCollision,
  resetGame,
  updateDirectionPlayer1,
  updateDirectionPlayer2,
  whereBallHitPlayer,
} from '@server/pongFunctions/pongFunctions';
import { setInterval } from 'timers';
import { PrismaService } from '@server/prisma/prisma.service';
import { AuthService } from '@server/auth/auth.service';

@WebSocketGateway({
  cors: {
    origin: process.env.FRONT_URL || 'http://localhost:3000',
    exposedHeaders: ['Authorization'],
    credentials: true,
    allowedHeaders: ['Authorization'],
  },
})
export class MyGateway implements OnModuleInit {
  @WebSocketServer()
  server: Server;

  constructor(
    private prisma: PrismaService,
    private authService: AuthService,
  ) {}

  // *Pong settings
  defaultWindowResolution: { winWidth: number; winHeight: number } = {
    winWidth: 1920,
    winHeight: 1080,
  };
  frameRate = 15;
  mode = 'normal'; // *mode de jeu(normal, mode1 ou mode2)
  ballSpeed = 2; // *vitesse de la balle (x10% en augmentant de 1)
  player1Speed = 2; // *vitesse joueur 1 (x10% en augmentant de 1)
  player2Speed = 2; // *vitesse joueur 2 (x10% en augmentant de 1)
  sizePlayer1 = 1; // *largeur du joueur (x10% en augmentant de 1)
  sizePlayer2 = 1; // *largeur du joueur (x10% en augmentant de 1)
  colorBackground = '#252930'; // *couleur background
  colorPlayer1 = '#141BFF'; // *couleur joueur 1 "#FF14FB"
  colorPlayer2 = '#F6751C'; // *couleur joueur 2 "#FF14FB"
  colorBall = '#FF14FB'; // *couleur de la ball
  colorScoreAndCenterLine = '#FF14FB'; // *couleur du score et de la ligne du milieu
  endScore = 5; // *score avant la fin d'une partie
  ballDirectionBeginning = 1; // *dans quelle direction va la balle au debut

  gameData: GameData[] = []; // *stocke toutes les parties de pong
  //   playersList: { id: string; name: string }[] = []; // *matchmaking queue
  playersList: {
    [mode: string]: { id: string; dbId: number; name: string | undefined }[];
  } = {}; // *matchmaking queue
  privatePlayersList: {
    [inviteCode: string]: {
      [mode: string]: { id: string; name: string; dbId: number }[];
    };
  } = {}; // *private matchmaking queue
  namesDb: { id: string; name: string; dbId: number }[] = []; // *stocke tous les noms avant de pouvoir jouer

  onModuleInit() {
    this.server.on('connection', async (socket) => {
      if (!socket.handshake.auth || !socket.handshake.auth.token) {
        return socket.disconnect();
      }

      if (
        !(await this.authService.isLoggedInFromToken(
          socket.handshake.auth.token,
        ))
      ) {
        return socket.disconnect();
      }
      const user = await this.authService.getLoggedInUserFromToken(
        socket.handshake.auth.token,
      );
      if (!user) {
        return socket.disconnect();
      }
      if (
        this.namesDb.find((element) => element.name === user.username) ===
        undefined
      ) {
        const newName = {
          id: socket.id,
          name: user.username,
          dbId: user.id,
        };
        this.namesDb.push(newName);
        socket.emit('nameNotAlreadyUsed', {
          name: user.username,
          id: socket.id,
          dbId: user.id,
        });
      }

      socket.on('checkPlayerName', () => {
        if (
          this.namesDb.find((element) => element.name === user.username) !==
          undefined
        ) {
          socket.emit('nameNotAlreadyUsed', {
            name: user.username,
            id: socket.id,
            dbID: user.id,
          });
        }
      });

      socket.on('searchPlayer', (info: { name: string; mode: string }) => {
        const infoPlayer: {
          id: string;
          dbId: number;
          name: string | undefined;
        } = {
          id: socket.id,
          name: undefined,
          dbId: user.id,
        };

        infoPlayer.name = this.namesDb.find(
          (element) => element.id == socket.id,
        )?.name;

        if (this.playersList[info.mode] === undefined)
          this.playersList[info.mode] = [];
        this.playersList[info.mode].push(infoPlayer);
        if (this.playersList[info.mode].length >= 2) {
          const p1Obj = {
            p1Info: this.playersList[info.mode][0],
            p1Side: 'right',
            sequenceNumber: 0,
          };
          const p2Obj = {
            p2Info: this.playersList[info.mode][1],
            p2Side: 'left',
            sequenceNumber: 0,
          };

          const PlayersObj: GameData = {
            p1: p1Obj,
            p2: p2Obj,
            pongData: new PongData(
              this.defaultWindowResolution.winWidth,
              this.defaultWindowResolution.winHeight,
              info.mode,
              this.ballSpeed,
              this.player1Speed,
              this.player2Speed,
              this.sizePlayer1,
              this.sizePlayer2,
              this.colorBackground,
              this.colorPlayer1,
              this.colorPlayer2,
              this.colorBall,
              this.colorScoreAndCenterLine,
              this.endScore,
              this.ballDirectionBeginning,
            ),
          };
          this.gameData.push(PlayersObj);
          this.playersList[info.mode].splice(0, 2);
          if (this.playersList[info.mode].length == 0)
            delete this.playersList[info.mode];

          this.server.emit('found', PlayersObj);
        }
      });

      socket.on('deletePrivateGame', (inviteCode: string) => {
        if (this.privatePlayersList[inviteCode] !== undefined) {
          delete this.privatePlayersList[inviteCode];
        }
      });

      socket.on('updateGame', (gameDataFront: GameData) => {
        if (gameDataFront) {
          const idGame = this.gameData.findIndex(
            (element: GameData) =>
              element.p1 &&
              gameDataFront.p1 &&
              element.p1.p1Info &&
              gameDataFront.p1.p1Info &&
              element.p1.p1Info.id === gameDataFront.p1.p1Info.id &&
              element.p2 &&
              gameDataFront.p2 &&
              element.p2.p2Info &&
              gameDataFront.p2.p2Info &&
              element.p2.p2Info.id === gameDataFront.p2.p2Info.id,
          );
          if (idGame !== -1) {
            this.gameData[idGame].pongData = gameDataFront.pongData;
          }
        }
      });

      socket.on('askRetry', (gameDataFront: GameData) => {
        if (gameDataFront) {
          const idGame = this.gameData.findIndex(
            (element: GameData) =>
              element.p1?.p1Info?.id === gameDataFront.p1?.p1Info?.id &&
              element.p2?.p2Info?.id === gameDataFront.p2?.p2Info?.id,
          );
          if (idGame !== -1) {
            if (
              gameDataFront.pongData?._player1Properties._retry &&
              gameDataFront.pongData?._player1Properties._retry > 0
            ) {
              this.gameData[idGame]!.pongData!._player1Properties._retry =
                gameDataFront.pongData?._player1Properties._retry;
            }
            if (
              gameDataFront.pongData?._player2Properties._retry &&
              gameDataFront.pongData?._player2Properties._retry > 0
            ) {
              if (this.gameData[idGame].pongData) {
                this.gameData[idGame]!.pongData!._player2Properties._retry =
                  gameDataFront.pongData?._player2Properties._retry;
              }
            }

            if (
              this.gameData[idGame]?.pongData?._player1Properties._retry ===
                1 &&
              this.gameData[idGame]?.pongData?._player2Properties._retry === 1
            ) {
              this.gameData[idGame]?.pongData?._player1Properties._retry === 0;
              this.gameData[idGame]?.pongData?._player2Properties._retry === 0;

              const p1Obj = {
                p1Info: this.gameData[idGame]?.p1?.p1Info,
                p1Side: 'right',
                sequenceNumber: 0,
              };
              const p2Obj = {
                p2Info: this.gameData[idGame]?.p2?.p2Info,
                p2Side: 'left',
                sequenceNumber: 0,
              };

              const PlayersObj: GameData = {
                p1: p1Obj,
                p2: p2Obj,
                pongData: new PongData(
                  this.defaultWindowResolution.winWidth,
                  this.defaultWindowResolution.winHeight,
                  gameDataFront.pongData?._mode,
                  this.ballSpeed,
                  this.player1Speed,
                  this.player2Speed,
                  this.sizePlayer1,
                  this.sizePlayer2,
                  this.colorBackground,
                  this.colorPlayer1,
                  this.colorPlayer2,
                  this.colorBall,
                  this.colorScoreAndCenterLine,
                  this.endScore,
                  this.ballDirectionBeginning,
                ),
              };
              this.gameData.push(PlayersObj);
              this.gameData.splice(idGame, 1);
              this.server.emit('found', this.gameData[idGame]);
            }
          }
        }
      });

      socket.on(
        'deletePlayerPrivateList',
        (info: { name: string | null; playerCode: string }) => {
          if (!this.privatePlayersList[info.playerCode]) {
            return;
          }
          const currentMode: string = Object.keys(
            this.privatePlayersList[info.playerCode],
          )[0];

          const removePlayerListId = this.privatePlayersList[info.playerCode][
            currentMode
          ].findIndex((element) => element.id === socket.id);
          if (removePlayerListId !== -1) {
            this.privatePlayersList[info.playerCode][currentMode].splice(
              removePlayerListId,
              1,
            );
          }
        },
      );

      socket.on(
        'createPrivateGame',
        (e: { inviteCode: string; mode: string }) => {
          this.privatePlayersList[e.inviteCode] = {};
          this.privatePlayersList[e.inviteCode][e.mode] = [];
          socket.emit('privateGameCreated', e.inviteCode);
        },
      );

      socket.on(
        'foundPrivate',
        async (e: { inviteCode: string; name: string }) => {
          console.log('Je suis dans found Private');
          if (e.inviteCode === null) socket.emit('codeNotValid');
          else if (this.privatePlayersList[e.inviteCode] === undefined) {
            socket.emit('gameNotFound');
          } else {
            const infoPlayer: {
              id: string;
              dbId: number;
              name: string;
            } = {
              id: socket.id,
              name: e.name,
              dbId: user.id,
            };

            const currentMode: string = Object.keys(
              this.privatePlayersList[e.inviteCode],
            )[0];

            if (
              this.privatePlayersList[e.inviteCode][currentMode].some(
                (e) => e.id === socket.id,
              )
            ) {
              socket.emit('alreadyInGame');
              return;
            }

            this.privatePlayersList[e.inviteCode][currentMode].push(infoPlayer);

            await this.prisma.user.update({
              where: {
                id: user.id,
              },
              data: {
                status: 'In game',
                inGame: true,
              },
            });

            if (
              this.privatePlayersList[e.inviteCode][currentMode].length >= 2
            ) {
              const p1Obj = {
                p1Info: this.privatePlayersList[e.inviteCode][currentMode][0],
                p1Side: 'right',
                sequenceNumber: 0,
              };
              const p2Obj = {
                p2Info: this.privatePlayersList[e.inviteCode][currentMode][1],
                p2Side: 'left',
                sequenceNumber: 0,
              };

              const PlayersObj: GameData = {
                p1: p1Obj,
                p2: p2Obj,
                pongData: new PongData(
                  this.defaultWindowResolution.winWidth,
                  this.defaultWindowResolution.winHeight,
                  currentMode,
                  this.ballSpeed,
                  this.player1Speed,
                  this.player2Speed,
                  this.sizePlayer1,
                  this.sizePlayer2,
                  this.colorBackground,
                  this.colorPlayer1,
                  this.colorPlayer2,
                  this.colorBall,
                  this.colorScoreAndCenterLine,
                  this.endScore,
                  this.ballDirectionBeginning,
                ),
              };
              this.gameData.push(PlayersObj);
              delete this.privatePlayersList[e.inviteCode];

              this.server.emit('found', PlayersObj);
            }
          }
        },
      );

      socket.on('watchPlayer', (playerToWatch: string) => {
        if (
          this.namesDb.find((e) => e.dbId.toString() === playerToWatch) ===
          undefined
        )
          socket.emit('playerNotFound');
        else {
          const gameId = this.gameData.findIndex(
            (e: GameData) =>
              (e.p1 &&
                e.p1.p1Info &&
                e.p1.p1Info.dbId.toString() === playerToWatch) ||
              (e.p2 &&
                e.p2.p2Info &&
                e.p2.p2Info.dbId.toString() === playerToWatch),
          );
          if (gameId !== -1) {
            let findGameId: string | undefined;
            let findGameSide: string | undefined;
            if (
              this.gameData[gameId].p1?.p1Info?.dbId.toString() ===
              playerToWatch
            ) {
              findGameId = this.gameData[gameId].p1?.p1Info?.id;
              findGameSide = this.gameData[gameId]?.p1?.p1Side;
            } else if (
              this.gameData[gameId]?.p2?.p2Info?.dbId.toString() ===
              playerToWatch
            ) {
              findGameId = this.gameData[gameId].p2?.p2Info?.id;
              findGameSide = this.gameData[gameId].p2?.p2Side;
            }

            socket.emit('watchGame', {
              playerIdBack: findGameId,
              playerSideBack: findGameSide,
              gameMode: this.gameData[gameId]?.pongData?._mode,
            });
          } else {
            // console.log('p1 === ');
            // console.log(this.gameData[0]?.p1?.p1Info?.name);
            // console.log('p2 === ');
            // console.log(this.gameData[0]?.p2?.p2Info?.name);
            socket.emit('noGameToWatch');
          }
        }
      });

      socket.on(
        'updateBall',
        async (dataObj: { gameData: GameData; sequenceNumber: number }) => {
          if (dataObj.gameData) {
            const gameDataFront = dataObj.gameData;
            const sequenceNumber = dataObj.sequenceNumber;
            const currentGameId = this.gameData.findIndex(
              (element: GameData) =>
                element.p1?.p1Info?.id === gameDataFront.p1?.p1Info?.id &&
                element.p2?.p2Info?.id === gameDataFront.p2?.p2Info?.id,
            );
            if (currentGameId !== -1) {
              if (this.gameData[currentGameId].pongData) {
                const currentGame = this.gameData[currentGameId];
                currentGame.pongData!._ballProperties._sequenceNumber =
                  sequenceNumber;
                currentGame.pongData!._ballProperties._x +=
                  currentGame.pongData!._ballProperties._speedX;
                currentGame.pongData!._ballProperties._y +=
                  currentGame.pongData!._ballProperties._speedY;

                if (
                  checkBallBoundsY(
                    currentGame.pongData!._ballProperties._y +
                      currentGame.pongData!._ballProperties._speedY,
                    currentGame.pongData,
                  )
                )
                  currentGame.pongData!._ballProperties._speedY *= -1;

                if (
                  checkBallCollision(
                    currentGame.pongData!._ballProperties,
                    currentGame.pongData!._player1Properties,
                    currentGame.pongData,
                  ) &&
                  currentGame.pongData!._ballProperties._speedX < 0
                ) {
                  if (
                    currentGame.pongData!._ballProperties._x <=
                    currentGame.pongData!._player1Properties._x +
                      currentGame.pongData!._player1Properties._width
                  ) {
                    updateDirectionPlayer1(
                      whereBallHitPlayer(
                        currentGame.pongData!._ballProperties,
                        currentGame.pongData!._player1Properties,
                      ),
                      currentGame.pongData!._ballProperties,
                      currentGame.pongData!,
                    );
                    currentGame.pongData!._ballProperties._speedX *= -1;
                  }
                } else if (
                  checkBallCollision(
                    currentGame.pongData!._ballProperties,
                    currentGame.pongData!._player2Properties,
                    currentGame.pongData!,
                  ) &&
                  currentGame.pongData!._ballProperties._speedX > 0
                ) {
                  if (
                    currentGame.pongData!._ballProperties._x +
                      currentGame.pongData!._ballProperties._width >=
                    currentGame.pongData!._player2Properties._x
                  ) {
                    updateDirectionPlayer2(
                      whereBallHitPlayer(
                        currentGame.pongData!._ballProperties,
                        currentGame.pongData!._player2Properties,
                      ),
                      currentGame.pongData!._ballProperties,
                      currentGame.pongData!,
                    );
                    currentGame.pongData!._ballProperties._speedX *= -1;
                  }
                }

                if (currentGame.pongData!._ballProperties._x < 0) {
                  currentGame.pongData!._player2Properties._score++;
                  if (
                    currentGame.pongData!._player2Properties._score <
                    this.endScore
                  ) {
                    if (currentGame.pongData!._mode === 'mode1') {
                      currentGame.pongData!._player1Properties._height *= 1.1;
                      currentGame.pongData!._player2Properties._height *= 0.9;
                    }
                    resetGame(1, currentGame.pongData!);
                  } else {
                    currentGame.pongData!._ballProperties._x =
                      currentGame.pongData!._pongCanvasWidth / 2;
                    currentGame.pongData!._ballProperties._y =
                      currentGame.pongData!._pongCanvasHeight / 2;
                    currentGame.pongData!._ballProperties._speedX = 0;
                    currentGame.pongData!._ballProperties._speedY = 0;
                    currentGame.pongData!._player2Properties._endResult =
                      'You won';
                    currentGame.pongData!._player1Properties._endResult =
                      'You lost';
                    try {
                      console.log({
                        loserScore: 0,
                        winnerScore: 0,
                        mode: currentGame.pongData!._mode,
                        loserId: currentGame.p2!.p2Info!.dbId,
                        winnerId: currentGame.p1!.p1Info!.dbId,
                      });
                      await this.prisma.game.create({
                        data: {
                          loserScore: 0,
                          winnerScore: 0,
                          mode: currentGame.pongData!._mode,
                          loserId: currentGame.p1!.p1Info!.dbId,
                          winnerId: currentGame.p2!.p2Info!.dbId,
                        },
                      });
                    } catch (e) {
                      console.log(e);
                    }
                    this.server.emit('endGame', this.gameData[currentGameId]);
                  }
                } else if (
                  currentGame.pongData!._ballProperties._x >
                  currentGame.pongData!._pongCanvasWidth
                ) {
                  currentGame.pongData!._player1Properties._score++;
                  if (
                    currentGame.pongData!._player1Properties._score <
                    this.endScore
                  ) {
                    if (currentGame.pongData!._mode === 'mode1') {
                      currentGame.pongData!._player2Properties._height *= 1.1;
                      currentGame.pongData!._player1Properties._height *= 0.9;
                    }
                    resetGame(-1, currentGame.pongData!);
                  } else {
                    currentGame.pongData!._ballProperties._x =
                      currentGame.pongData!._pongCanvasWidth / 2;
                    currentGame.pongData!._ballProperties._y =
                      currentGame.pongData!._pongCanvasHeight / 2;
                    currentGame.pongData!._ballProperties._speedX = 0;
                    currentGame.pongData!._ballProperties._speedY = 0;
                    currentGame.pongData!._player2Properties._endResult =
                      'You lost';
                    currentGame.pongData!._player1Properties._endResult =
                      'You won';
                    try {
                      console.log({
                        loserScore: 0,
                        winnerScore: 0,
                        mode: currentGame.pongData!._mode,
                        loserId: currentGame.p2!.p2Info!.dbId,
                        winnerId: currentGame.p1!.p1Info!.dbId,
                      });
                      await this.prisma.game.create({
                        data: {
                          loserScore: 0,
                          winnerScore: 0,
                          mode: currentGame.pongData!._mode,
                          loserId: currentGame.p2!.p2Info!.dbId,
                          winnerId: currentGame.p1!.p1Info!.dbId,
                        },
                      });
                    } catch (e) {
                      console.log(e);
                    }
                    this.server.emit('endGame', this.gameData[currentGameId]);
                  }
                }
              }
            }
          }
        },
      );

      socket.on(
        'keydown',
        (e: {
          keycode: string;
          side: string;
          gameData: GameData;
          sequenceNumberPlayer1: number;
          sequenceNumberPlayer2: number;
        }) => {
          if (e.keycode !== 'null' && e.gameData) {
            const currentGameId = this.gameData.findIndex(
              (element: GameData) =>
                element.p1?.p1Info?.id === socket.id ||
                element.p2?.p2Info?.id === socket.id,
            );
            if (currentGameId !== -1) {
              const side = e.side;
              const keycode = e.keycode;
              this.gameData[currentGameId]!.p1!.sequenceNumber =
                e.sequenceNumberPlayer1;
              this.gameData[currentGameId]!.p2!.sequenceNumber =
                e.sequenceNumberPlayer2;
              const currentPongGame = this.gameData[currentGameId].pongData;
              switch (keycode) {
                case 'KeyW':
                  if (
                    side === 'right' &&
                    currentPongGame &&
                    currentPongGame._player1Properties._y >= 0
                  ) {
                    currentPongGame._player1Properties._y -=
                      currentPongGame._player1Properties._speedY;
                  } else if (
                    side === 'left' &&
                    currentPongGame &&
                    currentPongGame._player2Properties._y >= 0
                  ) {
                    currentPongGame._player2Properties._y -=
                      currentPongGame._player2Properties._speedY;
                  }
                  break;
                case 'KeyS':
                  if (
                    side === 'right' &&
                    currentPongGame &&
                    currentPongGame._player1Properties._y <=
                      currentPongGame._pongCanvasHeight -
                        currentPongGame._player1Properties._height
                  ) {
                    currentPongGame._player1Properties._y +=
                      currentPongGame._player1Properties._speedY;
                  } else if (
                    side === 'left' &&
                    currentPongGame &&
                    currentPongGame._player2Properties._y <=
                      currentPongGame._pongCanvasHeight -
                        currentPongGame._player2Properties._height
                  ) {
                    currentPongGame._player2Properties._y +=
                      currentPongGame._player2Properties._speedY;
                  }
                  break;
              }
            }
          }
        },
      );

      socket.on('cancelSearch', async () => {
        await this.prisma.user.update({
          where: {
            id: user.id,
          },
          data: {
            status: 'online',
            inGame: false,
          },
        });
        for (const [key] of Object.entries(this.playersList)) {
          const removePlayerListId = this.playersList[key].findIndex(
            (element) => element.id === socket.id,
          );
          if (removePlayerListId !== -1) {
            this.playersList[key].splice(removePlayerListId, 1);
            if (this.playersList[key].length === 0)
              delete this.playersList[key];
          }
        }
      });

      socket.on('removeGameBackend', (removeGameData: GameData) => {
        if (removeGameData) {
          const removePongId = this.gameData.findIndex(
            (element: GameData) =>
              element.p1?.p1Info?.id === removeGameData.p1?.p1Info?.id &&
              element.p2?.p2Info?.id === removeGameData.p2?.p2Info?.id,
          );
          if (removePongId !== -1) {
            this.gameData.splice(removePongId, 1);
          }
        }
      });

      socket.on('quitPlayer', async (playerId: string) => {
        await this.prisma.user.update({
          where: {
            id: user.id,
          },
          data: {
            status: 'online',
            inGame: false,
          },
        });
        const removePongId = this.gameData.findIndex(
          (element: GameData) =>
            element.p1?.p1Info?.id === socket.id ||
            element.p2?.p2Info?.id === socket.id,
        );
        if (removePongId !== -1) {
          this.gameData.splice(removePongId, 1);
        }
        this.server.emit('disconnectPlayer', playerId);
      });

      socket.on('disconnect', () => {
        // * tests pour voir si je supprime bien tout lors de la deconnexion d'un client
        // console.log(`number of active game == ${this.gameData.length}`);
        // console.log(`number of client with name = ${this.namesDb.length}`);
        // console.log('playersList = ');
        // console.log(this.playersList);
        // console.log('privatePlayersList = ');
        // console.log(this.privatePlayersList);

        // *enleve la partie de pong
        let gameRemoved = null;
        const removePongId = this.gameData.findIndex(
          (element: GameData) =>
            element.p1?.p1Info?.id === socket.id ||
            element.p2?.p2Info?.id === socket.id,
        );
        if (removePongId !== -1) {
          gameRemoved = this.gameData[removePongId];
        }

        // *enleve personne si dans la queue
        for (const [key] of Object.entries(this.playersList)) {
          const removePlayerListId = this.playersList[key].findIndex(
            (element) => element.id === socket.id,
          );
          if (removePlayerListId !== -1) {
            this.playersList[key].splice(removePlayerListId, 1);
            if (this.playersList[key].length === 0)
              delete this.playersList[key];
          }
        }

        // *enleve personne si dans la queue privee
        for (const [key] of Object.entries(this.privatePlayersList)) {
          const currentMode = Object.keys(this.privatePlayersList[key])[0];
          const removePlayerListId = this.privatePlayersList[key][
            currentMode
          ].findIndex((element) => element.id === socket.id);
          if (removePlayerListId !== -1) {
            this.privatePlayersList[key][currentMode].splice(
              removePlayerListId,
              1,
            );
            if (this.privatePlayersList[key][currentMode].length === 0)
              delete this.privatePlayersList[key];
          }
        }

        // *enleve nom de la db
        const removeNameId = this.namesDb.findIndex(
          (element) => element.id === socket.id,
        );
        if (removeNameId !== -1) {
          this.namesDb.splice(removeNameId, 1);
        }

        this.server.emit('playerDisconnetion', gameRemoved);
      });

      setInterval(() => {
        this.server.emit('updateGame', this.gameData);
      }, this.frameRate);
    });
  }
}
