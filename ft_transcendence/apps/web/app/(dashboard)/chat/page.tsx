import { Button } from "@web/components/ui/button";
import Chats from "./_components/chats";
import { PlusSquare } from "lucide-react";
import {
	AlertDialog,
	AlertDialogTrigger,
} from "@web/components/ui/alert-dialog"
import NewChatButton from "./_components/alert";

export default function Home() {
	return (
		<>
			<div className="flex float-right">
				<NewChatButton />
			</div>
			<Chats />
		</>
	);
}
