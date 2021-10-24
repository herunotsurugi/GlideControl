void APlayerCharacterBase::MoveForward(float Value)
{
	//Check If Gliding
	if (GetExtendedMovementComponent()->IsCustomMovementMode(static_cast<uint8>(ECustomMovementMode::Glide)))
	{
		//Set FVector2D ControlInput X
		ControlInput.X = Value;
		return;
	}
}

void APlayerCharacterBase::MoveRight(float Value)
{
	//Check If Gliding
	if (GetExtendedMovementComponent()->IsCustomMovementMode(static_cast<uint8>(ECustomMovementMode::Glide)))
	{
		//Set FVector2D ControlInput Y
		ControlInput.Y = Value;
		return;
	}	
}


void APlayerCharacterBase::Tick(float DeltaSeconds)
{
	//Check If Gliding
	if (GetExtendedMovementComponent()->IsCustomMovementMode(static_cast<uint8>(ECustomMovementMode::Glide)))
	{
		//Check If Client Ignore This Line If Single Player
		if (IsLocallyControlled())
		{
			//Get Character Yaw Rotation
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			
			//Calcuate Control Vector By Getting Normal Of Forward And Right Vectors And Multiplying Them With Control Input X And Y 
			FVector ControlVector = (FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * ControlInput.X) +
				(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * ControlInput.Y).GetSafeNormal();
					
			//Interp Forward Vector To Control Vector To Get Move Direction
			const FRotator MoveDir = UKismetMathLibrary::RInterpTo(GetActorForwardVector().Rotation(), ControlVector.Rotation(), DeltaSeconds, 15.0f);

			//Get Movement Multiplier, This Is Keyboard Implementation For Controller May Need Modification
			const float MoveValue = FMath::Min(FMath::Abs(ControlInput.X) + FMath::Abs(ControlInput.Y), 1.0f);
			
			// Send Input 
			AddMovementInput(MoveDir.Quaternion().GetForwardVector(), MoveValue);
		}
	)
}