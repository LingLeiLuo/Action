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
    --通知开始，开始慢动作
    UE.UGameplayStatics.SetGlobalTimeDilation(MeshComp, 0.1)
    return true
end

-- function M:Received_NotifyTick(MeshComp, Animation, FrameDeltaTime)
-- end

function M:Received_NotifyEnd(MeshComp, Animation)
    --通知结束，恢复正常速度
    UE.UGameplayStatics.SetGlobalTimeDilation(MeshComp, 1)
    return true
end

return M