--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type ANS_ToggleWeaponCollision_C
local M = UnLua.Class()

function M:Received_NotifyBegin(MeshComp, Animation, TotalDuration)
    local ValidType = UE.EActionValidType.Valid
    local CombatComponent = UE.UActionFunctionLibrary.K2_GetPawnCombatComponentFromActor(MeshComp:GetOwner(), ValidType)

    if ValidType == UE.EActionValidType.Valid then
        local logString = UE.UKismetSystemLibrary.GetDisplayName(CombatComponent)
        logString = UE.UKismetStringLibrary.Concat_StrStr(logString, " is valid ")
        UE.UKismetSystemLibrary.PrintString(none, logString)
        print(logString)
    end

    return true
end

-- function M:Received_NotifyTick(MeshComp, Animation, FrameDeltaTime)
-- end

-- function M:Received_NotifyEnd(MeshComp, Animation)
-- end

return M