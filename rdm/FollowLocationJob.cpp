#include "FollowLocationJob.h"
#include "Rdm.h"
#include "leveldb/db.h"
#include "CursorInfo.h"

FollowLocationJob::FollowLocationJob(int i, const Location &loc, unsigned f)
    : Job(i), location(loc), flags(f)
{
}

FollowLocationJob::~FollowLocationJob()
{
}

void FollowLocationJob::execute()
{
    leveldb::DB *db = Server::instance()->db(Server::Symbol);
    CursorInfo cursorInfo = Rdm::findCursorInfo(db, location);
    if (isAborted())
        return;
    if (!cursorInfo.target.isNull()) {
        write(cursorInfo.target.key(flags));
    }
}
