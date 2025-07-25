import { PongData } from '@server/classes/Classes';

export type GameData = {
  p1:
    | {
        p1Info:
          | { id: string; dbId: number; name: string | undefined }
          | undefined;
        p1Side: string;
        sequenceNumber: number;
      }
    | undefined;
  p2:
    | {
        p2Info:
          | { id: string; dbId: number; name: string | undefined }
          | undefined;
        p2Side: string;
        sequenceNumber: number;
      }
    | undefined;
  pongData: PongData | undefined;
};
