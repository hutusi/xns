
#pragma once

#include "command.h"

#include <vector>

class CommandExecuter{
public:
	virtual void do_(Command* cmd){
		exec_cmds_.push_back(cmd);
		cmd->execute();
	}

	virtual void undo(){
		if (exec_cmds_.empty()) { return; }

		Command* cmd = exec_cmds_.back();
		undo_cmds_.push_back(cmd);
		exec_cmds_.pop_back();
		cmd->undo();
	}

	virtual void redo(){
		if (undo_cmds_.empty()) { return; }

		Command* cmd = undo_cmds_.back();
		exec_cmds_.push_back(cmd);
		undo_cmds_.pop_back();
		cmd->redo();
	}

	inline void clear_done() { exec_cmds_.clear(); }
	inline void clear_undo() { undo_cmds_.clear(); }
	inline void clear_all(){
		clear_done();
		clear_undo();
	}

private:
	std::vector<Command*> exec_cmds_;
	std::vector<Command*> undo_cmds_;
};
