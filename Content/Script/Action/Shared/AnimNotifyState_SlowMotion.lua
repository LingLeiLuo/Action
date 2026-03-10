--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type ANS_SlowMotion_C
local M = UnLua.Class()

function M:Received_NotifyBegin(MeshComp, Animation, TotalDuration)
    UE.UGameplayStatics.SetGlobalTimeDilation(MeshComp, 0.1)
    return true
end

-- function M:Received_NotifyTick(MeshComp, Animation, FrameDeltaTime)
-- end

function M:Received_NotifyEnd(MeshComp, Animation)
    UE.UGameplayStatics.SetGlobalTimeDilation(MeshComp, 1)
    return true
end

return M